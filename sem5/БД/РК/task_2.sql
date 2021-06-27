-- Инструкцию SELECT, использующую простое выражение CASE
-- Выводит менеджеров отделов, начальника и обычных сотрудников
SELECT employee_name, employee_salary,
        CASE (employee_post)
            WHEN 'Manager' THEN 'Head of department'
            WHEN 'chief' THEN 'Chief of company'
            ELSE 'Regular employee'
        END AS post
FROM employee;

-- Инструкцию, использующую оконную функцию
-- Выводит среднюю зарплату по отделам
SELECT DISTINCT department_name,
       avg(employee_salary) OVER (PARTITION BY department.department_id) AS AVG_SALARY
FROM department JOIN employee on employee.employee_department = department.department_id;

-- Инструкцию SELECT, консолидирующую данные с помощью предложения GROUP BY и предложения HAVING
-- Выводит отдел, в котором средняя зарплата меньше 1000
SELECT employee_department
FROM employee JOIN department d on employee.employee_department = d.department_id
GROUP BY employee_department
HAVING avg(employee_salary) < 1000;