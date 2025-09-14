-- Task 1  - Create Table
CREATE TABLE MyTable (
        id NUMBER,
        value NUMBER);
        
TRUNCATE TABLE MyTable; 

DROP TABLE MyTable;

SELECT * FROM MyTable;
--------------------------------------------------------------------------------        
-- Task 2 - insert data
BEGIN
    FOR i IN 1..10000 
    LOOP
        INSERT INTO MyTable(id,value) 
        VALUES (i,TRUNC(DBMS_RANDOM.VALUE(1, 10000)));
    END LOOP;
    
    COMMIT;
END;
--------------------------------------------------------------------------------
-- Task 3 - function calculating odds and evens
CREATE OR REPLACE FUNCTION is_evens_quantity_more RETURN VARCHAR2 IS
odd_amount NUMBER;
even_amount NUMBER;
BEGIN
    SELECT COUNT(*) INTO even_amount FROM MyTable WHERE MOD(value,2)=0;
    SELECT COUNT(*) INTO odd_amount FROM MyTable WHERE MOD(value,2)=1;
    
    IF even_amount > odd_amount THEN
        RETURN 'TRUE';
    ELSIF even_amount < odd_amount THEN
        RETURN 'FALSE';
    ELSE
        RETURN 'EQUAL';
    END IF;
    
END;

SET SERVEROUTPUT ON;

DECLARE
    result VARCHAR2(10);
BEGIN
    result := is_evens_quantity_more;
    DBMS_OUTPUT.PUT_LINE('Result: ' || result);
END;
--------------------------------------------------------------------------------
-- Task 4 - Function generating INSERT statement
CREATE OR REPLACE FUNCTION generate_insert(id NUMBER) RETURN VARCHAR2 IS
value NUMBER;
result_query VARCHAR2(100);
BEGIN
    SELECT t.value INTO value FROM MyTable t WHERE t.id=id AND ROWNUM = 1;
    result_query := 'INSERT INTO MyTable (id, value) VALUES (' || id || ', ' || value || ');';
    DBMS_OUTPUT.PUT_LINE(result_query);
    RETURN result_query;
END;

DECLARE
    result VARCHAR2(100);
BEGIN
    result := generate_insert(1);
END;
--------------------------------------------------------------------------------
-- Task 5 - DML procedures

-- Procedure 1 - INSERT
CREATE OR REPLACE PROCEDURE insert_data(id NUMBER, value NUMBER) IS
BEGIN
    INSERT INTO MyTable(id,value) VALUES (id, value);
END;

BEGIN
    insert_data(10001, 11);
END;

SELECT * FROM MyTable WHERE id=1;

-- Procedure 2 - DELETE
CREATE OR REPLACE PROCEDURE delete_data(p_id NUMBER) IS
BEGIN
    DELETE FROM MyTable t WHERE t.id=p_id;
END;

BEGIN
    delete_data(10001);
END;

-- Procedure 3 - UPDATE
CREATE OR REPLACE PROCEDURE update_data(p_id NUMBER, p_value NUMBER) IS
BEGIN
    UPDATE MyTable
    SET value=p_value
    WHERE id=p_id;
END;

BEGIN
    update_data(1, 42);
END;
--------------------------------------------------------------------------------
-- Task 6 - reward_counter

-- Helper function to determin whether the input can be converted to number
CREATE OR REPLACE FUNCTION Is_Number (input IN VARCHAR2) RETURN BOOLEAN IS
  res_number NUMBER;
BEGIN
  res_number := to_number (input);
  RETURN (TRUE);
EXCEPTION
  WHEN VALUE_ERROR THEN
    RETURN (FALSE);
END;


CREATE OR REPLACE FUNCTION count_yearly_reward(f_salary VARCHAR2, f_percent VARCHAR2) RETURN NUMBER IS
int_salary NUMBER;
int_percent NUMBER;
real_percent NUMBER;
reward NUMBER(14,2);

salary_negative EXCEPTION;
percent_incorrect EXCEPTION;
invalid_input EXCEPTION; 

BEGIN
    IF NOT Is_Number(f_salary) THEN
        RAISE invalid_input;
    END IF;
    int_salary := TO_NUMBER(f_salary);
    
    IF NOT Is_Number(f_percent) THEN
        RAISE invalid_input;
    END IF;
    int_percent := TO_NUMBER(f_percent);
    
    IF int_salary <=0 THEN
        RAISE salary_negative;
    END IF; 
    
    IF int_percent <=0 OR int_percent >=100 THEN
        RAISE percent_incorrect;
    END IF;    
        
    real_percent := int_percent/100;
    reward := (1 + real_percent)*12*int_salary;
    
    RETURN reward;
    
EXCEPTION    
    WHEN salary_negative THEN
        DBMS_OUTPUT.PUT_LINE('Salary cannot be negative');
        RETURN NULL;
    WHEN percent_incorrect THEN
        DBMS_OUTPUT.PUT_LINE('Percent must be from 1 to 99');
        RETURN NULL;    
     WHEN invalid_input THEN
        DBMS_OUTPUT.PUT_LINE('Invalid input data type.');
        RETURN NULL;
END;

SET SERVEROUTPUT ON;

DECLARE
    yearly_reward NUMBER;
BEGIN
    yearly_reward := count_yearly_reward('hfh', 4);
    DBMS_OUTPUT.PUT_LINE('Yearly reward: ' || yearly_reward);
END;


