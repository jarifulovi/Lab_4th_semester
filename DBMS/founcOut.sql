create or replace procedure query_emp(p_id in employees.employee_id%type,
p_name out employees.last_name%type,
p_salary out employees.salary%type) 
is 
begin
select last_name ,salary Into p_name,p_salary
from employee
where employee_id=p_id;
end query_emp;
/
Declare
v_emp_name employee.last_name%type;
v_emp_sal employee.salary%type;
begin
query_emp(171 , v_emp_name, V_emp_sal);
dbms_output.put_line(v_emp_name||' earns '||
to_char(v_emp_sal, '$999, 999.00'));
end;/