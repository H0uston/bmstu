-- 1. Инструкция SELECT, используящая предикат сравнения
-- Вывести имена и города всех заказчиков, сотруднячащих с компаниями в сфере энергии
SELECT c.id_customer, c.name_customer, c.city_customer
FROM customers AS c INNER JOIN cargo on c.id_customer = cargo.id_customer
INNER JOIN suppliers s on cargo.id_supplier = s.id_supplier
WHERE (s.sector_supplier = 'Energy')
ORDER BY c.id_customer;

-- 2. Инструкция SELECT, используящая предикат BETWEEN
-- Вывести всех заказчиков, чьи грузы прибыли в период с 1 января по 1 июня 2017 года
SELECT c.id_customer, c.name_customer, t.id_trip, t.end_data_trip
FROM customers AS c INNER JOIN cargo ON c.id_customer = cargo.id_customer
INNER JOIN trip t on cargo.id_trip = t.id_trip
WHERE t.end_data_trip BETWEEN '2017-01-01' AND'2017-06-01'
ORDER BY t.end_data_trip;

-- 3. Инструкция SELECT, использующая предикат LIKE
-- Вывести всех заказчиков, в чьих названиях есть "Company"
SELECT c.name_customer
FROM customers AS c
WHERE (c.name_customer LIKE '%Company%');

-- 4. Инструкция SELECT, использующая предикат IN с вложенным подзапросом
-- Вывести всех поставщика, отправивщих посылки весом меньше 10
SELECT s.id_supplier, s.name_supplier, c.weight_cargo
FROM suppliers AS s
JOIN cargo c on s.id_supplier = c.id_supplier
WHERE s.id_supplier IN
    (
        SELECT cargo.id_supplier FROM cargo
        WHERE (cargo.weight_cargo < 10)
    ) AND c.weight_cargo < 10
ORDER BY s.id_supplier;

-- 5. Инструкция SELECT, использующая предикат EXISTS с вложенным подзапросом
-- Вывести всех поставщиков из одного города
SELECT c.id_customer, c.name_customer
FROM customers AS c
WHERE EXISTS
    (
        SELECT c.id_customer
        FROM cargo INNER JOIN suppliers s on cargo.id_supplier = s.id_supplier
        WHERE c.city_customer = s.city_supplier
    );

-- 6. Инструкция SELECT, использующая предикат сравнения с квантором
-- Вывести самую позднюю дату прибытия груза
SELECT trip.end_data_trip
FROM trip
WHERE trip.end_data_trip >= ALL
    (
        SELECT trip.end_data_trip FROM trip
    );

-- 7. Инструкция SELECT, использующая агрератную функцию в выражениях столбцов
-- Вывести средний вес груза в отрасли технологий
SELECT AVG(weight_cargo)
FROM cargo JOIN suppliers s on cargo.id_supplier = s.id_supplier
WHERE s.sector_supplier = 'Technology';

-- 8. Инструкция SELECT, использующая скалярные подзапросы в выражениях столбцов
-- Вевести среднее и максимальное значение веса грузов в отрасли здравоохранения
SELECT DISTINCT suppliers.sector_supplier,
    (
        SELECT avg(weight_cargo) FROM cargo
        JOIN suppliers s on cargo.id_supplier = s.id_supplier
        WHERE s.sector_supplier = 'Health Care'
    ) AS avg_finance_weight,
    (
        SELECT max(weight_cargo) FROM cargo
        JOIN suppliers s on cargo.id_supplier = s.id_supplier
        WHERE s.sector_supplier = 'Health Care'
    ) AS max_finance_weight
FROM suppliers
WHERE sector_supplier = 'Health Care';

-- 9. Инструкция SELECT, использующая простое выражение CASE
-- Вывести откуда, куда и в каком году двигался груз
SELECT trip.from_trip, trip.to_trip, trip.start_date_trip,
        CASE (date_part('year', trip.start_date_trip))
            WHEN '2019' THEN 'This year'
            WHEN '2018' THEN 'Last year'
            WHEN '2020' THEN 'Next year'
            ELSE 'Some years ago'
        END AS When
FROM trip;

-- 10. Инструкция SELECT, использующая поисковое выражение CASE
-- Вывести поставщиков, заказчиков и тип веса посылки
SELECT suppliers.name_supplier, customers.name_customer, weight_cargo,
       CASE
            WHEN weight_cargo < 100 THEN 'Easy'
            WHEN weight_cargo < 500 THEN 'Middle'
            WHEN weight_cargo > 500 THEN 'Hard'
        END AS Type
FROM customers JOIN cargo c on customers.id_customer = c.id_customer
JOIN suppliers on c.id_supplier = suppliers.id_supplier
ORDER BY weight_cargo;

-- 11. Создание новой временной локальной таблицы из результирующего набора данных инструкции SELECT
-- Создать таблицу содержащую id рейса и его длительность весом меньше 100
SELECT trip.id_trip, date_part('day', age(trip.end_data_trip, trip.start_date_trip)) AS duration
INTO trip_duration
FROM trip INNER JOIN cargo c on trip.id_trip = c.id_trip
WHERE c.weight_cargo < 100;
-- 12. Инструкция SELECT, использующая вложенные коррелированные подзапросы в качестве производных таблиц в предложении FROM
-- Вывести всех поставщиков, которые отправляли грузы
SELECT cargo.id_supplier
FROM cargo
WHERE EXISTS
    (
        SELECT id_supplier
        FROM suppliers
        WHERE (cargo.id_supplier = suppliers.id_supplier)
    );
-- 13. Инструкция SELECT, использующая вложенные подзапросы с уровнем вложенности 3
-- Вывести всех поставщиков, у которых вес груза равен минимальному весу груза среди заказчиков, айди которыз меньше максимального
-- айди заказчкика среди тех у кого индекс заказчика больше среднего индекса заказчика, у которых имя компании состоит из Inc
SELECT suppliers.id_supplier
FROM suppliers JOIN cargo on suppliers.id_supplier = cargo.id_supplier
WHERE cargo.weight_cargo =
    (
        SELECT min(cargo.weight_cargo)
        FROM cargo
        WHERE cargo.id_customer <
        (
            SELECT max(id_customer)
            FROM customers
            WHERE index_customer >
            (
                SELECT avg(index_customer)
                FROM customers
                WHERE name_customer LIKE '%Inc%'
            )
        )
    );
-- 14. Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY, но без предложения HAVING
-- Вывести все отрасли, их средний и минимальный вес
SELECT sector_supplier, avg(cargo.weight_cargo), min(cargo.weight_cargo)
FROM suppliers JOIN cargo on suppliers.id_supplier = cargo.id_supplier
GROUP BY sector_supplier;
-- 15. Инструкция SELECT, консолидирующая данные с помощью предложения GROUP BY и предложения HAVING
-- Вывести все отрасли, имеющий средний вес меньше 450, их средний и минимальный вес
SELECT sector_supplier, avg(cargo.weight_cargo), min(cargo.weight_cargo)
FROM suppliers JOIN cargo on suppliers.id_supplier = cargo.id_supplier
GROUP BY sector_supplier
HAVING avg(weight_cargo) < 450;
-- 16. Однострочная инструкция INSERT, выполняющая вставку в таблицу результирующего набора данных вложенного подзапроса
--
INSERT INTO customers (id_customer, name_customer, city_customer, index_customer) VALUES
(101, 'BMSTU', 'Moscow', 143300);
-- 17. Многострочная инструкция INSERT, выполняющая вставку в таблицу результирующего набора данных вложенного подзапроса
--
INSERT INTO customers (id_customer, name_customer, city_customer, index_customer) VALUES
(103, 'KFC', 'Chita', (SELECT max(index_customer) FROM customers WHERE index_customer > 140000));
-- 18. Простая инструкция UPDATE
-- Изменить значения у всех грузов весом больше 500
UPDATE cargo
SET weight_cargo = weight_cargo * 0.9
WHERE cargo.weight_cargo > 500;
-- 19. Инструкция UPDATE со скалярным подзапросом в предложении SET
-- Изменить значения у всех грузов весом меньше 10
UPDATE cargo
SET weight_cargo =
    (
        SELECT avg(weight_cargo) FROM cargo
        WHERE weight_cargo < 10
    )
WHERE weight_cargo < 10;
-- 20. Простая инструкция DELETE
-- удалить все id меньшие 100
DELETE FROM trip_duration
WHERE id_trip <= 100;
DROP TABLE trip_duration;
-- 21. Инструкция DELETE с вложенным коррелированным подзапросом в предложении WHERE
-- Удалить всех поставщиков с айди больше 1000
DELETE FROM cargo
WHERE EXISTS
    (
        SELECT suppliers.id_supplier
        FROM suppliers
        WHERE cargo.id_supplier = suppliers.id_supplier AND cargo.id_supplier > 1000
    );
-- 22. Инструкция SELECT, использующая простое обобщение табличное выражение
-- Вывести максимальный вес груза на каждого заказчика
WITH CTE(max_weight, max_weight_customer)
AS
    (
        SELECT max(cargo.weight_cargo), cargo.id_customer
        FROM cargo
        GROUP BY cargo.id_customer
    )
SELECT *
FROM CTE;
-- 23. Инструкция SELECT, использующая рекурсивное обобщенное табличное выражение
-- Вывести список поставщиков и всех его заказчиков
ALTER TABLE suppliers ADD COLUMN owner integer;

WITH RECURSIVE CTE AS (
    -- стартовая часть рекурсии
    SELECT s.id_supplier, s.owner, 0 as Level
    FROM suppliers as s
    WHERE owner is NULL AND s.id_supplier = 42

    UNION ALL

    -- рекурсивная часть
    SELECT s.id_supplier, s.owner, c.level + 1
    FROM suppliers s INNER JOIN CTE as c ON s.owner = c.id_supplier

)
SELECT id_supplier, owner, level FROM CTE;
-- 24. Оконные функции. Использование конструкции MIN/MAX/AVG OVER()
-- Вывести отрасль, ее средние, максимальные и минимальные значения
SELECT DISTINCT suppliers.sector_supplier,
       avg(cargo.weight_cargo) OVER (PARTITION BY suppliers.sector_supplier) AS AVG_WEIGHT,
       max(cargo.weight_cargo) OVER (PARTITION BY suppliers.sector_supplier) AS MAX_WEIGHT,
       min(cargo.weight_cargo) OVER (PARTITION BY suppliers.sector_supplier) AS MIN_WEIGHT
FROM suppliers JOIN cargo on suppliers.id_supplier = cargo.id_supplier;
-- 25. Оконные функции на устранение дублей
-- Показать дубли по весу
SELECT weight_cargo,
       row_number() over (PARTITION BY weight_cargo ORDER BY weight_cargo),
       rank() over(ORDER BY weight_cargo) as rnk
FROM cargo c;


WITH C AS
(
  SELECT *,
    ROW_NUMBER() OVER(PARTITION BY weight_cargo
                      ORDER BY id_customer) AS n
  FROM cargo
)
SELECT * FROM C
WHERE n = 1;


-- Задание на дополнительные баллы
CREATE TABLE Table1
(
    id integer,
    var1 text,
    valid_from_dttm date,
    valid_to_dttm date
);

CREATE TABLE Table2
(
    id integer,
    var2 text,
    valid_from_dttm date,
    valid_to_dttm date
);

INSERT INTO Table1 (id, var1, valid_from_dttm, valid_to_dttm) VALUES (1, 'A', '2018-09-01', '2018-09-15');
INSERT INTO Table1 (id, var1, valid_from_dttm, valid_to_dttm) VALUES (1, 'B', '2018-09-16', '5999-12-31');

INSERT INTO Table2 (id, var2, valid_from_dttm, valid_to_dttm) VALUES (1, 'A', '2018-09-01', '2018-09-18');
INSERT INTO Table2 (id, var2, valid_from_dttm, valid_to_dttm) VALUES (1, 'B', '2018-09-19', '5999-12-31');

SELECT Table1.id, Table1.var1, Table2.var2,
CASE WHEN Table1.valid_from_dttm < Table2.valid_from_dttm THEN Table2.valid_from_dttm ELSE Table1.valid_from_dttm END AS valid_from_dttm,
CASE WHEN Table1.valid_to_dttm > Table2.valid_to_dttm THEN Table2.valid_to_dttm ELSE Table1.valid_to_dttm END AS valid_to_dttm
FROM Table1
INNER JOIN Table2 ON Table1.id = Table2.id AND Table1.valid_from_dttm < Table2.valid_to_dttm AND Table2.valid_from_dttm < Table1.valid_to_dttm
;

DROP TABLE Table1;

DROP TABLE Table2;

