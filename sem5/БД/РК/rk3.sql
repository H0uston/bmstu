drop table if exists filial;
drop table if exists employee;

drop table filial, employee cascade;

truncate filial, employee cascade;

-- 1.1

create table if not exists filial (
	id bigserial not null primary key,
	name varchar(30) not null,
	address varchar(30) not null,
	phone varchar(10) not null
);

create table if not exists employee (
	id bigserial not null primary key,
	name varchar(30) not null,
	date date not null,
	otdel varchar(30) not null,
	code bigint not null references filial(id)
);

insert into filial (name, address, phone)
values
('Moscovskiy', 'Gerzena, 5', '456-78-23'),
('Novosib', 'Proletar, 8', '543-62-34'),
('Saratov', 'Shukhova, 44', '452-56-11'),
('Tom', 'Gerzena, 7', '987-46-74');

select * from filial;

insert into employee (name, date, otdel, code)
values
('Ivanov Ivan', '25-09-1990', 'it', 1),
('Petrov Petr', '12-11-1987', 'buch', 3),
('Dud Petr', '02-08-1983', 'buch', 1);

select * from filial;
select * from employee;

-- 1.2

create or replace function min_count_of_employee()
returns varchar as $$
	with cte (name, count)
	AS
	(
		select f.name, count(*)
		from employee as e
		inner join filial as f on e.code = f.id
		group by e.code, f.name
	)
	select name
	from cte
	order by count
	limit 1;
$$ language sql;

select min_count_of_employee();

-- 2.1

-- 2.2

create or replace function func_22()
returns table(name varchar)  as $$
	with cte (name, count)
	AS
	(
		select f.name, count(*)
		from filial as f
		inner join employee as e on e.code = f.id
		where date_part('year', age(e.date)) = 29
		group by e.code, f.name
	)
	select name
	from cte
	where count >= 2 and count <= 15
$$ language sql;

select * from func_22();

-- 2.3
create or replace function emp_without_7()
returns table(id bigint, name varchar, fil varchar, phone varchar) as $$
	select distinct e.id, e.name, f.name, f.phone
	from employee as e join filial as f on f.id = e.code
	where f.phone not like '%7%'
$$ language sql;

select * from emp_without_7();