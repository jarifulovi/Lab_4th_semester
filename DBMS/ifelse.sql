CREATE OR REPLACE FUNCTION tax(p_value IN NUMBER)
 RETURN NUMBER IS
BEGIN
   RETURN (((p_value * nvl(employees.commission_pct, 0)) + p_value) * 0.08 * 12);
END tax;
/
SELECT employee_id, last_name, salary * 12, tax(salary)
FROM   employees
WHERE  department_id = 100;


CREATE OR REPLACE FUNCTION tax(p_value IN NUMBER)
RETURN NUMBER IS
   v_commission_pct employees.commission_pct%TYPE;
BEGIN
   SELECT commission_pct INTO v_commission_pct FROM employees WHERE rownum = 1;
   RETURN (((p_value * NVL(v_commission_pct, 0)) + p_value) * 0.08 * 12);
EXCEPTION
   WHEN NO_DATA_FOUND THEN
      RETURN (p_value * 0.08 * 12); -- Assuming default tax rate when no commission percentage is found
END tax;
/


CREATE OR REPLACE FUNCTION tax(p_value IN NUMBER)
RETURN NUMBER IS
   v_commission_pct NUMBER;
BEGIN
   SELECT NVL(commission_pct, 0) INTO v_commission_pct FROM employees;
   RETURN (((p_value * v_commission_pct) + p_value) * 0.08 * 12);
END tax;
/


SET SERVEROUTPUT ON


DECLARE
    v_input_value char(1);
BEGIN
    v_input_value := '&input';
    IF v_input_value BETWEEN '0' AND '9' THEN
        DBMS_OUTPUT.PUT_LINE('The input is a number.');
    ELSIF v_input_value BETWEEN 'A' AND 'Z' THEN
        DBMS_OUTPUT.PUT_LINE('The input is an uppercase letter.');
    ELSIF v_input_value BETWEEN 'a' AND 'z' THEN
        DBMS_OUTPUT.PUT_LINE('The input is a lowercase letter.');
    ELSE
        DBMS_OUTPUT.PUT_LINE('The input is a special character.');
    END IF;
END;
/
