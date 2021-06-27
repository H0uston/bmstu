-- Вариант 1
-- Уласик
-- ИУ7 - 51Б
-- Создать базу данных RK2. Создать в ней структуру, соответствующую указанной на ER-диаграмме. Заполнить таблицы тестовыми значениями (не менее 10 в каждой таблице).

CREATE TABLE employee
(
    employee_id integer NOT NULL,
    employee_department integer,
    employee_post text NOT NULL,
    employee_name text NOT NULL,
    employee_salary float4 NOT NULL,
    PRIMARY KEY (employee_id)
);


CREATE TABLE department
(
    department_id integer NOT NULL,
    department_name text NOT NULL,
    department_phone_number integer NOT NULL,
    department_manager integer,
    PRIMARY KEY (department_id)
);

ALTER TABLE employee ADD FOREIGN KEY (employee_department) REFERENCES department (department_id);
ALTER TABLE department ADD FOREIGN KEY (department_manager) REFERENCES employee (employee_id);

DROP TABLE department CASCADE;
DROP TABLE employee CASCADE;

INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (1, 1, 'chief', 'Vladimir Putin', 2000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (2, 1, 'secretary', 'Joseph Joestar', 100000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (3, 2, 'programmer', 'Joseph Stalin', 10.3);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (4, 2, 'Manager', 'Vladimir Rurikovich', 40000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (5, 3, 'cleaner', 'Vladimir Lenin', 9.2);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (6, 3, 'Manager', 'Dmitriy Medvedev', 500);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (7, 4, 'Manager', 'Leonhard Euler', 100000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (8, 4, 'accountant', 'Mikhail Lomonosov', 90000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (9, 5, 'Designer', 'Artem Lebedev', 1000000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (10, 6, 'Engineer', 'Peter Romanov', 250000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (11, 6, 'Manager', 'Alex Romanov', 350000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (12, 7, 'Doctor', 'Nikolay Pirogov', 40000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (13, 8, 'Chemist', 'Nikita Yakovlev', 100000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (14, 8, 'Manager', 'Alex Usanyov', 120000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (15, 9, 'Guard', 'Peter Peterson', 20000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (16, 10, 'Seller', 'Maria Matrova', 80000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (17, 10, 'Seller', 'Boris Kaminskiy', 135000);
INSERT INTO employee (employee_id, employee_department, employee_post, employee_name, employee_salary)
VALUES (18, 11, 'Cook', 'Igor Potrin', 30000);

INSERT INTO department (department_id, department_name, department_phone_number, department_manager)
VALUES (1, 'authority', 1255135233, 1);
INSERT INTO department (department_id, department_name, department_phone_number, department_manager)
VALUES (2, 'programmers', 1255135243, 4);
INSERT INTO department (department_id, department_name, department_phone_number, department_manager)
VALUES (3, 'cleaners', 1255135200, 6);
INSERT INTO department (department_id, department_name, department_phone_number, department_manager)
VALUES (4, 'accounting', 115133000, 7);
INSERT INTO department (department_id, department_name, department_phone_number, department_manager)
VALUES (5, 'designers', 12532, 9);
INSERT INTO department (department_id, department_name, department_phone_number, department_manager)
VALUES (6, 'engineers', 64323, 11);
INSERT INTO department (department_id, department_name, department_phone_number, department_manager)
VALUES (7, 'doctors', 42231, 12);
INSERT INTO department (department_id, department_name, department_phone_number, department_manager)
VALUES (8, 'chemists', 36420, 14);
INSERT INTO department (department_id, department_name, department_phone_number, department_manager)
VALUES (9, 'security', 23532, 15);
INSERT INTO department (department_id, department_name, department_phone_number, department_manager)
VALUES (10, 'sellers', 643234, 16);
INSERT INTO department (department_id, department_name, department_phone_number, department_manager)
VALUES (11, 'cooks', 2353222, 18);

CREATE TABLE medicament
(
    medicament_id integer NOT NULL REFERENCES employee (employee_id),
    medicament_name text NOT NULL,
    medicament_instruction text NOT NULL,
    medicament_cost float4 NOT NULL,
    PRIMARY KEY (medicament_id)
);

INSERT INTO medicament (medicament_id, medicament_name, medicament_instruction, medicament_cost)
VALUES (1, 'Noshpa', 'Eat it', 1222);
INSERT INTO medicament (medicament_id, medicament_name, medicament_instruction, medicament_cost)
VALUES (2, 'Nuraphen', 'Drink it', 1300);
INSERT INTO medicament (medicament_id, medicament_name, medicament_instruction, medicament_cost)
VALUES (3, 'Bandage', 'You can use it', 300);
INSERT INTO medicament (medicament_id, medicament_name, medicament_instruction, medicament_cost)
VALUES (4, 'Morfine', 'Painkiller', 10000);
INSERT INTO medicament (medicament_id, medicament_name, medicament_instruction, medicament_cost)
VALUES (5, 'Lektoz', 'For headache', 1300);
INSERT INTO medicament (medicament_id, medicament_name, medicament_instruction, medicament_cost)
VALUES (6, 'Heal pills', 'Heal you', 5900);
INSERT INTO medicament (medicament_id, medicament_name, medicament_instruction, medicament_cost)
VALUES (7, 'Lemon party pills', 'For lemon party', 1223);
INSERT INTO medicament (medicament_id, medicament_name, medicament_instruction, medicament_cost)
VALUES (8, 'Placebo', 'Best pills!', 602);
INSERT INTO medicament (medicament_id, medicament_name, medicament_instruction, medicament_cost)
VALUES (9, 'Fear pills', 'For brave men', 30000);
INSERT INTO medicament (medicament_id, medicament_name, medicament_instruction, medicament_cost)
VALUES (10, 'Pills of night vision', 'For night', 9000);