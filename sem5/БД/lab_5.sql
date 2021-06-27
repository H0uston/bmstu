-- 1. Извлечь данные из таблиц

COPY  (select to_json(suppliers) from suppliers)
TO '/Users/houston/Documents/GitHub/Databases/Cargo_transportation/lab_5/suppliers.txt';

COPY (select to_json(customers) from customers)
TO '/Users/houston/Documents/GitHub/Databases/Cargo_transportation/lab_5/customers.txt';

COPY  (select to_json(trip) from trip)
TO '/Users/houston/Documents/GitHub/Databases/Cargo_transportation/lab_5/trip.txt';

COPY  (select to_json(cargo) from cargo)
TO '/Users/houston/Documents/GitHub/Databases/Cargo_transportation/lab_5/cargo.txt';

-- 2 Импортировать данные в таблицу

CREATE OR REPLACE PROCEDURE import_json_to_table()
as $$
    f = open('/Users/houston/Documents/GitHub/Databases/Cargo_transportation/lab_5/trip.txt')
    plan = plpy.prepare("INSERT INTO trip (SELECT * FROM json_to_record($1) as (id_trip integer, from_trip text, to_trip text, start_date_trip timestamp, end_date_trip timestamp))", ["json"])

    for line in f:
        plpy.execute(plan, [line])
    $$ LANGUAGE plpythonu;

INSERT INTO trip (id_trip, from_trip, to_trip, start_date_trip, end_data_trip)

select * from trip;

call import_json_to_table();


CREATE TABLE workers
(
    id_worker integer,
    name_worker text,
    PRIMARY KEY (id_worker)
);

CREATE TABLE vacation_types
(
    id_vacation_types integer,
    type_vacation_types text,
    PRIMARY KEY (id_vacation_types)
);

CREATE TABLE vacation
(
    id_vacation integer,
    id_worker_vacation integer REFERENCES workers (id_worker),
    date_vacation date,
    id_vacation_types integer REFERENCES vacation_types (id_vacation_types),
    PRIMARY KEY (id_vacation)
);

DROP TABLE vacation;

INSERT INTO workers VALUES (1, 'aaa');
INSERT INTO workers VALUES (2, 'bbb');
INSERT INTO workers VALUES (3, 'ccc');

INSERT INTO vacation_types VALUES (1, 'За свой счёт');
INSERT INTO vacation_types VALUES (2, 'Ежегодный отпуск');
INSERT INTO vacation_types VALUES (3, 'По болезни');

INSERT INTO vacation VALUES (1, 1, '01-09-20', 1);
INSERT INTO vacation VALUES (2, 1, '01-10-20', 1);
INSERT INTO vacation VALUES (3, 1, '05-01-20', 2);
INSERT INTO vacation VALUES (4, 1, '05-02-20', 2);
INSERT INTO vacation VALUES (5, 1, '05-03-20', 2);
INSERT INTO vacation VALUES (6, 2, '02-04-20', 3);


with tbl as (
    select *, lag(date_vacation) over
                  (partition by id_worker_vacation, id_vacation_types order by id_worker_vacation, date_vacation) as prev,
              lead(date_vacation) over
                  (partition by id_worker_vacation, id_vacation_types order by id_worker_vacation, date_vacation) as next,
              count(*) over (partition by id_worker_vacation, id_vacation_types order by id_worker_vacation, date_vacation) as cnt
    from vacation
)
select name_worker as fio, type_vacation_types as type,  tbl.date_vacation as date_from, t.date_vacation as date_to  from tbl
        join tbl t on tbl.id_worker_vacation = t.id_worker_vacation
        join workers on tbl.id_worker_vacation = workers.id_worker
        join vacation_types on tbl.id_vacation_types = vacation_types.id_vacation_types
        and t.date_vacation - tbl.date_vacation <= t.cnt
        and t.date_vacation >= tbl.date_vacation
        and tbl.id_vacation_types = t.id_vacation_types
        and ((tbl.prev is null or tbl.prev + interval '1 day' < tbl.date_vacation)
            and (t.next is null or t.date_vacation + interval '1 day' < t.next));


SELECT * FROM workers;
SELECT * FROM vacation_types;
SELECT * FROM vacation;






