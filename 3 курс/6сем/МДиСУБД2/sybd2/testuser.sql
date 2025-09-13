BEGIN
  EXECUTE IMMEDIATE 'DROP TABLE meal_categories CASCADE CONSTRAINTS';
EXCEPTION
  WHEN OTHERS THEN IF SQLCODE != -942 THEN RAISE; END IF;
END;
/
BEGIN
  EXECUTE IMMEDIATE 'DROP TABLE meals CASCADE CONSTRAINTS';
EXCEPTION
  WHEN OTHERS THEN IF SQLCODE != -942 THEN RAISE; END IF;
END;
/

CREATE TABLE meal_categories (
  category_id   NUMBER PRIMARY KEY,
  category_name VARCHAR2(100) NOT NULL
);

CREATE TABLE meals (
  meal_id     NUMBER PRIMARY KEY,
  meal_name   VARCHAR2(100) NOT NULL,
  price       NUMBER(6,2),
  calories    NUMBER,
  category_id NUMBER,
  CONSTRAINT fk_meal_category FOREIGN KEY (category_id) REFERENCES meal_categories(category_id)
);


INSERT INTO meal_categories (category_id, category_name) VALUES (1, 'Salads');
INSERT INTO meal_categories (category_id, category_name) VALUES (2, 'Main Dishes');
INSERT INTO meal_categories (category_id, category_name) VALUES (3, 'Desserts');
INSERT INTO meal_categories (category_id, category_name) VALUES (4, 'Beverages');
COMMIT;

INSERT INTO meals (meal_id, meal_name, price, calories, category_id) VALUES (1, 'Caesar Salad with Chicken', 450.00, 320, 1);
INSERT INTO meals (meal_id, meal_name, price, calories, category_id) VALUES (2, 'Vegetable Salad', 300.00, 150, 1);
INSERT INTO meals (meal_id, meal_name, price, calories, category_id) VALUES (3, 'Beef Stroganoff with Potatoes', 650.00, 600, 2);
INSERT INTO meals (meal_id, meal_name, price, calories, category_id) VALUES (4, 'Mushroom Risotto', 550.00, 480, 2);
INSERT INTO meals (meal_id, meal_name, price, calories, category_id) VALUES (5, 'Cheesecake', 400.00, 420, 3);
COMMIT;


SELECT * FROM meal_categories;
SELECT * FROM meals;
-------------------------------------------------------------------------------
--формируем динамические запросы из джэйсон файлов
CREATE OR REPLACE PROCEDURE dynamic_sql_procedure(
  p_json    IN  CLOB,
  p_cursor  OUT SYS_REFCURSOR,
  p_rows    OUT NUMBER,
  p_message OUT VARCHAR2
)
AS
  v_json_obj          JSON_OBJECT_T;
  v_query_type        VARCHAR2(50);

  v_select_columns      VARCHAR2(32767);
  v_tables              VARCHAR2(32767);
  v_join_conditions     VARCHAR2(32767);
  v_where_conditions    VARCHAR2(32767);
  v_subquery_conditions VARCHAR2(32767);
  v_group_by            VARCHAR2(32767);
  v_filter_clause       VARCHAR2(32767);

  v_query VARCHAR2(32767);

  v_table      VARCHAR2(100);
  v_columns    VARCHAR2(32767);
  v_values     VARCHAR2(32767);
  v_set_clause VARCHAR2(32767);

  v_ddl_command      VARCHAR2(50);
  v_fields           VARCHAR2(32767);
  v_generate_trigger VARCHAR2(5);
  v_trigger_name     VARCHAR2(100);
  v_pk_field         VARCHAR2(100);
  v_sequence_name    VARCHAR2(100);
  v_trigger_sql      VARCHAR2(32767);

BEGIN
  v_json_obj := JSON_OBJECT_T.parse(p_json);
  v_query_type := UPPER(v_json_obj.get_String('query_type'));

  IF v_query_type = 'SELECT' THEN
    v_select_columns := v_json_obj.get_String('select_columns');
    v_tables := v_json_obj.get_String('tables');
    BEGIN
      v_join_conditions := v_json_obj.get_String('join_conditions');--извлекаем
    EXCEPTION WHEN NO_DATA_FOUND THEN
      v_join_conditions := NULL;
    END;
    BEGIN
      v_where_conditions := v_json_obj.get_String('where_conditions');
    EXCEPTION WHEN NO_DATA_FOUND THEN
      v_where_conditions := NULL;
    END;
    BEGIN
      v_subquery_conditions := v_json_obj.get_String('subquery_conditions');
    EXCEPTION WHEN NO_DATA_FOUND THEN
      v_subquery_conditions := NULL;
    END;
    BEGIN
      v_group_by := v_json_obj.get_String('group_by');
    EXCEPTION WHEN NO_DATA_FOUND THEN
      v_group_by := NULL;
    END;
--подготавливаем. проверяем что не пустые и формируем часть
    v_filter_clause := NULL;
    IF v_join_conditions IS NOT NULL AND TRIM(v_join_conditions) IS NOT NULL THEN
      v_filter_clause := v_join_conditions;
    END IF;
    IF v_where_conditions IS NOT NULL AND TRIM(v_where_conditions) IS NOT NULL THEN
      IF v_filter_clause IS NOT NULL THEN
        v_filter_clause := v_filter_clause || ' AND ' || v_where_conditions;
      ELSE
        v_filter_clause := v_where_conditions;
      END IF;
    END IF;
    IF v_subquery_conditions IS NOT NULL AND TRIM(v_subquery_conditions) IS NOT NULL THEN
      IF v_filter_clause IS NOT NULL THEN
        v_filter_clause := v_filter_clause || ' AND ' || v_subquery_conditions;
      ELSE
        v_filter_clause := v_subquery_conditions;
      END IF;
    END IF;

    v_query := 'SELECT ' || v_select_columns || ' FROM ' || v_tables;
    IF v_filter_clause IS NOT NULL AND TRIM(v_filter_clause) IS NOT NULL THEN
      v_query := v_query || ' WHERE ' || v_filter_clause;
    END IF;
    IF v_group_by IS NOT NULL AND TRIM(v_group_by) IS NOT NULL THEN
      v_query := v_query || ' GROUP BY ' || v_group_by;
    END IF;

    p_message := 'Executing SELECT query.';
    p_rows    := 0;
    OPEN p_cursor FOR v_query;

  ELSIF v_query_type IN ('INSERT', 'UPDATE', 'DELETE') THEN
    v_table := v_json_obj.get_String('table');
    IF v_query_type = 'INSERT' THEN
      v_columns := v_json_obj.get_String('columns');
      v_values  := v_json_obj.get_String('values');
      v_query   := 'INSERT INTO ' || v_table || ' (' || v_columns || ') VALUES (' || v_values || ')';

    ELSIF v_query_type = 'UPDATE' THEN
      v_set_clause := v_json_obj.get_String('set_clause');
      BEGIN
        v_where_conditions := v_json_obj.get_String('where_conditions');
      EXCEPTION WHEN NO_DATA_FOUND THEN
        v_where_conditions := NULL;
      END;
      BEGIN
        v_subquery_conditions := v_json_obj.get_String('subquery_conditions');
      EXCEPTION WHEN NO_DATA_FOUND THEN
        v_subquery_conditions := NULL;
      END;

      v_filter_clause := NULL;
      IF v_where_conditions IS NOT NULL AND TRIM(v_where_conditions) IS NOT NULL THEN
        v_filter_clause := v_where_conditions;
      END IF;
      IF v_subquery_conditions IS NOT NULL AND TRIM(v_subquery_conditions) IS NOT NULL THEN
        IF v_filter_clause IS NOT NULL THEN
          v_filter_clause := v_filter_clause || ' AND ' || v_subquery_conditions;
        ELSE
          v_filter_clause := v_subquery_conditions;
        END IF;
      END IF;

      v_query := 'UPDATE ' || v_table || ' SET ' || v_set_clause;
      IF v_filter_clause IS NOT NULL AND TRIM(v_filter_clause) IS NOT NULL THEN
        v_query := v_query || ' WHERE ' || v_filter_clause;
      END IF;

    ELSIF v_query_type = 'DELETE' THEN
      BEGIN
        v_where_conditions := v_json_obj.get_String('where_conditions');
      EXCEPTION WHEN NO_DATA_FOUND THEN
        v_where_conditions := NULL;
      END;
      BEGIN
        v_subquery_conditions := v_json_obj.get_String('subquery_conditions');
      EXCEPTION WHEN NO_DATA_FOUND THEN
        v_subquery_conditions := NULL;
      END;

      v_filter_clause := NULL;
      IF v_where_conditions IS NOT NULL AND TRIM(v_where_conditions) IS NOT NULL THEN
        v_filter_clause := v_where_conditions;
      END IF;
      IF v_subquery_conditions IS NOT NULL AND TRIM(v_subquery_conditions) IS NOT NULL THEN
        IF v_filter_clause IS NOT NULL THEN
          v_filter_clause := v_filter_clause || ' AND ' || v_subquery_conditions;
        ELSE
          v_filter_clause := v_subquery_conditions;
        END IF;
      END IF;

      v_query := 'DELETE FROM ' || v_table;
      IF v_filter_clause IS NOT NULL AND TRIM(v_filter_clause) IS NOT NULL THEN
        v_query := v_query || ' WHERE ' || v_filter_clause;
      END IF;
    END IF;

    p_message := 'DML query ' || v_query_type || ' done.';
    p_cursor  := NULL;
    EXECUTE IMMEDIATE v_query;
    p_rows := SQL%ROWCOUNT;

  ELSIF v_query_type = 'DDL' THEN
    v_ddl_command := UPPER(v_json_obj.get_String('ddl_command'));
    v_table := v_json_obj.get_String('table');

    IF v_ddl_command = 'CREATE TABLE' THEN
      v_fields := v_json_obj.get_String('fields');
      v_query := 'CREATE TABLE ' || v_table || ' (' || v_fields || ')';
      EXECUTE IMMEDIATE v_query;
      p_message := 'Table ' || v_table || ' created.';
      p_rows    := 0;
      p_cursor  := NULL;

      BEGIN
        v_generate_trigger := v_json_obj.get_String('generate_trigger');
      EXCEPTION WHEN NO_DATA_FOUND THEN
        v_generate_trigger := 'false';
      END;

      IF LOWER(v_generate_trigger) = 'true' THEN
        v_trigger_name  := v_json_obj.get_String('trigger_name');
        v_pk_field      := v_json_obj.get_String('pk_field');
        v_sequence_name := v_json_obj.get_String('sequence_name');

        BEGIN
          EXECUTE IMMEDIATE 'CREATE SEQUENCE ' || v_sequence_name;
        EXCEPTION WHEN OTHERS THEN
          NULL;
        END;

        v_trigger_sql :=
          'CREATE OR REPLACE TRIGGER ' || v_trigger_name || ' ' ||
          'BEFORE INSERT ON ' || v_table || ' ' ||
          'FOR EACH ROW ' ||
          'WHEN (new.' || v_pk_field || ' IS NULL) ' ||
          'BEGIN ' ||
          '  SELECT ' || v_sequence_name || '.NEXTVAL INTO :new.' || v_pk_field || ' FROM dual; ' ||
          'END;';
        EXECUTE IMMEDIATE v_trigger_sql;
        p_message := p_message || ' Trigger ' || v_trigger_name || ' created.';
      END IF;

    ELSIF v_ddl_command = 'DROP TABLE' THEN
      v_query := 'DROP TABLE ' || v_table;
      EXECUTE IMMEDIATE v_query;
      p_message := 'Table ' || v_table || ' dropped.';
      p_rows    := 0;
      p_cursor  := NULL;
    ELSE
      RAISE_APPLICATION_ERROR(-20001, 'Wrong DDL command: ' || v_ddl_command);
    END IF;

  ELSE
    RAISE_APPLICATION_ERROR(-20001, 'Wrong query: ' || v_query_type);
  END IF;

EXCEPTION
  WHEN OTHERS THEN
    p_message := 'ERROR: ' || SQLERRM;
    p_rows    := 0;
    p_cursor  := NULL;
END dynamic_sql_procedure;
/

DROP PROCEDURE dynamic_sql_procedure;
-------------------------------------------------------------------------------
SET SERVEROUTPUT ON;

DECLARE
  v_json_input CLOB := '{
    "query_type": "SELECT",
    "select_columns": "m.meal_id, m.meal_name, m.price, m.calories, c.category_name",
    "tables": "meals m, meal_categories c",
    "join_conditions": "m.category_id = c.category_id",
    "where_conditions": "m.price > 300"
  }';

  v_cursor  SYS_REFCURSOR;
  v_rows    NUMBER;
  v_message VARCHAR2(4000);

  v_meal_id    NUMBER;
  v_meal_name  VARCHAR2(100);
  v_price      NUMBER(6,2);
  v_calories   NUMBER;
  v_category_name VARCHAR2(100);

BEGIN
  dynamic_sql_procedure(
    p_json    => v_json_input,
    p_cursor  => v_cursor,
    p_rows    => v_rows,
    p_message => v_message
  );

  DBMS_OUTPUT.PUT_LINE('Message: ' || v_message);

  LOOP
    FETCH v_cursor INTO v_meal_id, v_meal_name, v_price, v_calories, v_category_name;
    EXIT WHEN v_cursor%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Meal ID: ' || v_meal_id || ', Meal Name: ' || v_meal_name ||
                         ', Price: ' || v_price || ', Calories: ' || v_calories || ', Category: ' || v_category_name);
  END LOOP;

  CLOSE v_cursor;
END;
---------------------------------------------------------------------------------------------------------------------
DECLARE
  v_json_input CLOB := '{
    "query_type": "SELECT",
    "select_columns": "m.meal_id, m.meal_name, m.price, m.calories, c.category_name",
    "tables": "meals m, meal_categories c",
    "join_conditions": "m.category_id = c.category_id",
    "where_conditions": "m.price > 300",
    "subquery_conditions": "EXISTS (SELECT 1 FROM meals WHERE price < 600 AND category_id = m.category_id)"
  }';

  v_cursor  SYS_REFCURSOR;
  v_rows    NUMBER;
  v_message VARCHAR2(4000);

  v_meal_id    NUMBER;
  v_meal_name  VARCHAR2(100);
  v_price      NUMBER(6,2);
  v_calories   NUMBER;
  v_category_name VARCHAR2(100);

BEGIN
  dynamic_sql_procedure(
    p_json    => v_json_input,
    p_cursor  => v_cursor,
    p_rows    => v_rows,
    p_message => v_message
  );

  DBMS_OUTPUT.PUT_LINE('Message: ' || v_message);

  LOOP
    FETCH v_cursor INTO v_meal_id, v_meal_name, v_price, v_calories, v_category_name;
    EXIT WHEN v_cursor%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('Meal ID: ' || v_meal_id || ', Meal Name: ' || v_meal_name ||
                         ', Price: ' || v_price || ', Calories: ' || v_calories || ', Category: ' || v_category_name);
  END LOOP;

  CLOSE v_cursor;
END;
------------------------------------------------------------------------------------------------------------------------
DECLARE
  v_json_input CLOB := '{
    "query_type": "INSERT",
    "table": "meals",
    "columns": "meal_id, meal_name, price, calories, category_id",
    "values": "6, ''Spaghetti Bolognese'', 350, 500, 2"
  }';

  v_cursor  SYS_REFCURSOR;
  v_rows    NUMBER;
  v_message VARCHAR2(4000);

BEGIN
  dynamic_sql_procedure(
    p_json    => v_json_input,
    p_cursor  => v_cursor,
    p_rows    => v_rows,
    p_message => v_message
  );

  DBMS_OUTPUT.PUT_LINE('Message: ' || v_message);
  DBMS_OUTPUT.PUT_LINE('Rows affected: ' || v_rows);
END;
--------------------------------------------------------------------------------
DECLARE
  v_json_input CLOB := '{
    "query_type": "UPDATE",
    "table": "meals",
    "set_clause": "price = price * 1.10",
    "where_conditions": "category_id = 2",
    "subquery_conditions": "meal_id IN (SELECT meal_id FROM meals WHERE price < 900)"
  }';

  v_cursor  SYS_REFCURSOR;
  v_rows    NUMBER;
  v_message VARCHAR2(4000);

BEGIN
  dynamic_sql_procedure(
    p_json    => v_json_input,
    p_cursor  => v_cursor,
    p_rows    => v_rows,
    p_message => v_message
  );

  DBMS_OUTPUT.PUT_LINE('Message: ' || v_message);
  DBMS_OUTPUT.PUT_LINE('Rows affected: ' || v_rows);
END;
-------------------------------------------------------------------------------------------------------
DECLARE
  v_json_input CLOB := '{
    "query_type": "DELETE",
    "table": "meals",
    "where_conditions": "calories < 400",
    "subquery_conditions": "meal_id IN (SELECT meal_id FROM meals WHERE category_id = 3)"
  }';

  v_cursor  SYS_REFCURSOR;
  v_rows    NUMBER;
  v_message VARCHAR2(4000);

BEGIN
  dynamic_sql_procedure(
    p_json    => v_json_input,
    p_cursor  => v_cursor,
    p_rows    => v_rows,
    p_message => v_message
  );

  DBMS_OUTPUT.PUT_LINE('Message: ' || v_message);
  DBMS_OUTPUT.PUT_LINE('Rows affected: ' || v_rows);
END;
-------------------------------------------------------------------------------------------
DECLARE
  v_json_input CLOB := '{
    "query_type": "DDL",
    "ddl_command": "CREATE TABLE",
    "table": "created_table",
    "fields": "id NUMBER, name VARCHAR2(50)"
  }';

  v_cursor  SYS_REFCURSOR;
  v_rows    NUMBER;
  v_message VARCHAR2(4000);

BEGIN
  dynamic_sql_procedure(
    p_json    => v_json_input,
    p_cursor  => v_cursor,
    p_rows    => v_rows,
    p_message => v_message
  );

  DBMS_OUTPUT.PUT_LINE('Сообщение: ' || v_message);
END;
/
--------------------------------------------------------------------------------

DECLARE
  v_json_input CLOB := '{
    "query_type": "DDL",
    "ddl_command": "DROP TABLE",
    "table": "created_table"
  }';

  v_cursor  SYS_REFCURSOR;
  v_rows    NUMBER;
  v_message VARCHAR2(4000);

BEGIN
  dynamic_sql_procedure(
    p_json    => v_json_input,
    p_cursor  => v_cursor,
    p_rows    => v_rows,
    p_message => v_message
  );

  DBMS_OUTPUT.PUT_LINE('Сообщение: ' || v_message);
END;
--------------------------------------------------------------------------------
DECLARE
  v_json_input CLOB := '{
    "query_type": "DDL",
    "ddl_command": "CREATE TABLE",
    "table": "table_created_with_trigger",
    "fields": "id NUMBER, data VARCHAR2(20)",
    "generate_trigger": "true",
    "trigger_name": "created_table_trigger",
    "pk_field": "id",
    "sequence_name": "table_seq"
  }';

  v_cursor  SYS_REFCURSOR;
  v_rows    NUMBER;
  v_message VARCHAR2(4000);

BEGIN
  dynamic_sql_procedure(
    p_json    => v_json_input,
    p_cursor  => v_cursor,
    p_rows    => v_rows,
    p_message => v_message
  );

  DBMS_OUTPUT.PUT_LINE('Сообщение: ' || v_message);
END;

SELECT * FROM table_created_with_trigger;
DROP TABLE table_created_with_trigger;

DECLARE
  v_json_input CLOB := '{
    "query_type": "INSERT",
    "table": "table_created_with_trigger",
    "columns": "data",
    "values": "''First entry''"
  }';

  v_cursor  SYS_REFCURSOR;
  v_rows    NUMBER;
  v_message VARCHAR2(4000);

BEGIN
  dynamic_sql_procedure(
    p_json    => v_json_input,
    p_cursor  => v_cursor,
    p_rows    => v_rows,
    p_message => v_message
  );

  DBMS_OUTPUT.PUT_LINE('Сообщение: ' || v_message);
  DBMS_OUTPUT.PUT_LINE('Затронуто строк: ' || v_rows);
END;
-------------------------------------------------------------------------------
