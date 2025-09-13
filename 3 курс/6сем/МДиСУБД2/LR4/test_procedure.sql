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

GRANT CREATE TABLE TO C##MY_USER;
GRANT CREATE SEQUENCE TO C##MY_USER;
GRANT CREATE TRIGGER TO C##MY_USER;