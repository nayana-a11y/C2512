--Exercise 01: Add two numbers 
DROP PROCEDURE sp_find_sum_and_display;
CREATE OR REPLACE PROCEDURE sp_find_sum_and_display(first IN number, second IN number)
AS   
    s number := 0;
BEGIN 
    s := first + second;
    DBMS_OUTPUT.PUT_LINE('Sum of ' || first || ' and ' || second || ' is ' || s);
END;
-- to call the procedure 
call sp_find_sum_and_display(11, 21);
