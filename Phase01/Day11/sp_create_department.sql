
--Exercise 50:
DROP PROCEDURE sp_create_department;

CREATE OR REPLACE PROCEDURE sp_create_department(
    p_department_name IN VARCHAR2)
AS
    v_department_id number := 1;
    v_department_count number := 0;

BEGIN
    -- read department count
    select count(*) into v_department_count 
    from departments 
    where name = p_department_name;

    

    savepoint start_transaction;
        if v_department_count >= 1 then
            select id into v_department_id 
            from departments 
            where name = p_department_name;
        else 
            select (nvl(max(id),0) + 1) into v_department_id 
            from departments;

            INSERT INTO departments(id, name)
            VALUES (v_department_id, p_department_name);

            DBMS_OUTPUT.PUT_LINE('Department ' || p_department_name || ' is added');
        end if;
    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
       ROLLBACK TO start_transaction;
       DBMS_OUTPUT.PUT_LINE('Error occurred in creating employees: ' || SQLERRM);
END;


-- call the procedure sp_create_department
call sp_create_department('Maintainance');

select * from departments;
