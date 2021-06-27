-- 1. Определяемую пользователем скалярную функцию CLR (pl/python)
-- Функция, которая определяет количество посылок по имени компании
create or replace function count_of_cargo(company_name text) returns integer as
$$
query = 'select * from cargo JOIN customers c on c.id_customer = cargo.id_customer'
cursor = plpy.cursor(query)
count = 0
while True:
    rows = cursor.fetch(100)
    if not rows:
        break
    for row in rows:
        if row["name_customer"] == company_name:
            count += 1
return count
$$ language plpythonu;

select count_of_cargo('Petroquest Energy Inc');

SELECT count(*) FROM cargo
JOIN customers c on c.id_customer = cargo.id_customer
WHERE c.name_customer = 'Petroquest Energy Inc';

-- 2. Пользовательскую агрегатную функцию CLR
-- Функция среднего значения
create or replace function avg_state(prev real[2], next real) returns real[2] as
$$
return prev if next == 0 or next == None else [0 if prev[0] == None else prev[0] + next, prev[1] + 1]
$$ language plpythonu;

create or replace function avg_final(num real[2]) returns numeric as
$$
return 0 if num[1] == 0 else num[0] / num[1]
$$ language plpythonu;

drop aggregate if exists my_avg(numeric);
create aggregate my_avg(real) (
    sfunc = avg_state,
    stype =real[],
    finalfunc =avg_final,
    initcond = '{0,0}'
    );

select my_avg(weight_cargo) from cargo;

SELECT avg(weight_cargo) FROM cargo;

-- 3. Определяемую пользователем табличную функцию CLR,
drop function cargo_info_from_city(city text);
create or replace function cargo_info_from_city(city text)
    returns table
            (
                id             integer,
                company        text,
                start_date     timestamp,
                end_data       timestamp
            )
as
$$
query = "SELECT * from cargo \
JOIN customers on cargo.id_customer = customers.id_customer \
JOIN trip on cargo.id_trip = trip.id_trip \
WHERE city_customer = '{}'"

result = plpy.execute(query.format(city))
return [(r['id_customer'], r['name_customer'], r['start_date_trip'], r['end_data_trip']) for r in result]
$$ language plpythonu;

select cargo_info_from_city('Moscow');

SELECT cargo.id_customer, name_customer, start_date_trip, end_data_trip from cargo
JOIN customers on cargo.id_customer = customers.id_customer
JOIN trip on cargo.id_trip = trip.id_trip
WHERE city_customer = 'Moscow';

-- Хранимую процедуру
CREATE OR REPLACE PROCEDURE count_suppliers()
AS $$
    cnt = 0
    for i in plpy.cursor("select * from suppliers"):
        cnt += 1
    plpy.info(cnt)
$$ LANGUAGE plpythonu;

call count_suppliers();

SELECT count(*) FROM suppliers;

-- TRIGGER
create or replace function update_36_supplier() returns trigger as
$delete_empty_supplier$
query = "select count(*) from suppliers where sector_supplier = '{}'"
new_sector_value = TD["new"]["sector_supplier"]
count = plpy.execute(query.format(new_sector_value), 1)
if count != 0:
    update_query = "update suppliers set sector_supplier = 'n/a' where id_supplier = 36"
    plpy.execute(update_query, 0)
return None;
$delete_empty_supplier$
language plpythonu;

drop trigger check_number on suppliers;
create trigger check_number after insert on suppliers
    for each row
execute procedure update_36_supplier();

insert into suppliers (id_supplier, name_supplier, city_supplier, sector_supplier, owner) values
(130, 'KFI', 'LA', 'Basic Industries', null);

-- Определяемый пользователем тип
create type company; -- (имя компании, индекс)

create or replace function company_in(cstring) returns company
as
'ab_4.so',
'company_in'
    language C immutable
               strict;

create or replace function company_out(company) returns cstring
as
'/Users/houston/Documents/GitHub/Databases/Cargo_transportation/lab_4/lab_4.so',
'company_out'
    language C immutable
               strict;


create type company (
    input = company_in,
    output = company_out
    );

drop type company cascade;
select '(BMSTU, 0)'::company;

CREATE TABLE test
(
    info company,
    phone integer
);
DROP TABLE test;
INSERT INTO test (info, phone) VALUES ('BMSTU, 0'::company, 12124421);
SELECT * FROM test;
