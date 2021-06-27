-- 1. Скалярная функция
-- Считает кол-во заказчиков

CREATE FUNCTION count_customers() RETURNS bigint AS
'
	SELECT count(*) FROM customers
'
LANGUAGE SQL;

SELECT * FROM count_customers();


-- 2. Подставляемая табличная функция
-- Выводит поставщиков с их отраслями

CREATE FUNCTION get_suppliers_with_sector() RETURNS table(supplier_name text, sector text) AS
'
    SELECT name_supplier, sector_supplier FROM suppliers
'
LANGUAGE SQL;

SELECT  * FROM get_suppliers_with_sector();


-- 3. Многооператорная табличная функция
-- Считает количество кораблей данного типа

CREATE FUNCTION count_suppliers_by_sector(ttt text) RETURNS table(type_ text, cnt bigint) AS
$$
declare
	cnt BIGINT := 0;
	s text;
begin
	for s in select sector_supplier from suppliers
	loop
		if s = ttt THEN
			cnt = cnt + 1;
		end if;
	end loop;
	return query select ttt, cnt;
end
$$ LANGUAGE plpgsql;

SELECT * FROM count_suppliers_by_sector('Finance');


-- 4. Рекурсивную функцию или функцию с рекурсивным ОТВ
-- Выводит всю иерархию компаний и их дочерних компаний

CREATE OR REPLACE FUNCTION recurs_family(id_ integer) RETURNS table(id_1 integer, par_id integer, name text) AS
$$
    declare r record;
    begin
    return query select S.id_supplier, S.owner, S.name_supplier from suppliers as S
	where S.id_supplier = id_;
    for r in select S.id_supplier, S.owner, S.name_supplier from suppliers AS S
    where S.owner = id_
    loop
        raise info '%', r;
        return query select * from recurs_family(r.id_supplier);
	end loop;
    end;
$$ LANGUAGE plpgsql;

select * from recurs_family(59);

DROP FUNCTION recurs_family(id_ integer);


-- 5. Хранимая процедура
-- Считает количество городов, в которых находятся заказчики

CREATE OR REPLACE PROCEDURE count_cities() AS
$$
    declare cnt bigint = 0;
        r record;
    begin
        for r in select DISTINCT city_customer from customers
        loop
            cnt = cnt + 1;
        end loop;
        raise info '%', cnt;
    end;
$$ LANGUAGE plpgsql;

call count_cities();


-- 6. Рекурсивная хранимая процедура

CREATE OR REPLACE PROCEDURE recurs_family_p(id_ integer)  AS
$$
    declare r record;
    begin
    select S.id_supplier, S.owner, S.name_supplier from suppliers as S
	where S.id_supplier = id_ into r;
    raise info '%', r;
    for r in select S.id_supplier, S.owner, S.name_supplier from suppliers AS S
    where S.owner = id_
    loop
        call recurs_family_p(r.id_supplier);
	end loop;
    end;
$$ LANGUAGE plpgsql;

call recurs_family_p(42);
-- 7. Хранимая процедура с курсором
--

create procedure count_type_cursor(t text) AS
$$
  declare cnt bigint = 0;
      r record;
      curs cursor for select * from suppliers AS S where S.sector_supplier = t;
  begin
      for r in curs
      loop
          cnt = cnt + 1;
      end loop;
  raise info '%', cnt;
  end;
$$ language plpgsql;

call count_type_cursor('Finance');

-- 8. Хранимая процедура доступа к метаданным
-- Выводит информацию о всех таблицах

CREATE OR REPLACE PROCEDURE all_tables() AS
$$
    declare r record;
    begin
        for r in select * from information_schema.tables WHERE table_schema = 'public'
        loop
            raise info '%', r;
        end loop;
    end;
$$ language plpgsql;

call all_tables();


-- 9. Триггер AFTER
-- Если добавляется компания в городе'Astana', то этот имя города изменяется на 'Nur-Sultan'
-- Если удаляется компания в городе 'Astana' или 'Nur-Sultan', то добавляется такой же элемент с id + 1 и городом 'Moscow'

create or replace function trigger_after() returns trigger AS
$$
    begin
        if tg_op = 'INSERT' then
            if new.city_supplier = 'Astana' then
                update suppliers set city_supplier = 'Nur-Sultan' WHERE id_supplier = new.id_supplier;
            end if;
        elseif tg_op = 'DELETE' then
            if old.city_supplier = 'Nur-Sultan' or old.city_supplier = 'Astana' then
                insert into suppliers (id_supplier, name_supplier, city_supplier, sector_supplier, owner) values
                (old.id_supplier + 1, old.name_supplier, 'Moscow', old.sector_supplier, old.owner);
            end if;
        end if;
        return null;
    end;
$$ LANGUAGE plpgsql;

create trigger tr1 after insert or delete on suppliers
for each row execute function trigger_after();

drop trigger tr1 ON suppliers;

select * from suppliers
WHERE city_supplier = 'Astana';

insert into suppliers (id_supplier, name_supplier, city_supplier, sector_supplier, owner) values
(200, 'Kazahstan Co', 'Astana', 'Finance', null);

delete from suppliers where id_supplier = 200;


-- 10. Триггер INSTEAD OF
-- Меняет сектор с n\a на education

create or replace function trigger_instead_of() returns trigger as
$$
    begin
        update suppliers
        set sector_supplier = 'Education' where sector_supplier = 'n/a';
        return new;
    end;
$$ language plpgsql;

create trigger tr2 instead of update on suppliers_v
for each row execute function trigger_instead_of();

create view suppliers_v as
select * from suppliers;

drop trigger tr2 on suppliers_v;

select * from suppliers
ORDER BY sector_supplier;

update suppliers_v
set owner = null
where city_supplier = 'Moscow';