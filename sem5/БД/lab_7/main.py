# coding=utf-8
import re

from sqlalchemy import create_engine, MetaData, text
from sqlalchemy.orm import mapper, Session

db_string = 'postgresql://houston:admin@localhost:5433/transportation'
engine = create_engine(db_string)
meta = MetaData()
meta.reflect(bind=engine, schema='public')


class Customer(object):
    def __init__(self, id, name, city, index):
        self.id_customer = id
        self.name_customer  = name
        self.city_customer  = city
        self.index_customer  = index

    def __repr__(self):
        return 'id: {}, customer_name: {}, customer_city: {}, customer_index: {}'.format(
            self.id_customer, self.name_customer, self.city_customer, self.index_customer
        )


class Trip(object):
    def __init__(self, id, from_place, to_place, start_date, end_date):
        self.trip_id = id
        self.trip_from_place = from_place
        self.trip_to_place = to_place
        self.trip_start_date = start_date
        self.trip_end_date = end_date

    def __repr__(self):
        return 'id: {}, from_place: {}, to_place: {}, start_date: {}, end_date: {}'.format(
            self.trip_id, self.trip_from_place, self.trip_to_place, self.trip_start_date, self.trip_end_date
        )

    def __str__(self):
        return 'id: {}, from_place: {}, to_place: {}, start_date: {}, end_date: {}'.format(
            self.trip_id, self.trip_from_place, self.trip_to_place, self.trip_start_date, self.trip_end_date
        )


class Supplier(object):
    def __init__(self, id, name, city, sector, owner):
        self.supplier_id = id
        self.supplier_name = name
        self.supplier_city = city
        self.supplier_sector = sector
        self.owner = owner

    def __repr__(self):
        return 'id: {}, name: {}, city: {}, sector: {}, owner: {}'.format(
            self.supplier_id, self.supplier_name, self.supplier_city, self.supplier_sector, self.owner
        )


class Cargo(object):
    def __init__(self, id_customer, id_supplier, id_trip, weight_cargo):
        self.id_customer = id_customer
        self.id_supplier = id_supplier
        self.id_trip = id_trip
        self.weight_cargo = weight_cargo
        self.id = {id_customer, id_supplier, id_trip}

    def __repr__(self):
        return 'id_customer: {}, id_supplier: {}, id_trip: {}, weight: {}'.format(
            self.id_customer, self.id_supplier, self.id_trip,
            self.weight_cargo
        )


mapper(Customer, meta.tables['public.customers'])
mapper(Trip, meta.tables['public.trip'])
mapper(Supplier, meta.tables['public.suppliers'])
mapper(Cargo, meta.tables['public.cargo'])


# Analogs of connected objects
def engine_info():
    print('name: {}, driver: {}, url: {}'.format(
        engine.name, engine.driver, engine.url
    ))


def count_customers():
    conn = Session(bind=engine)
    count = conn.execute(
        text('select count(*) from public.customers')
    ).fetchone()[0]
    conn.close()
    print(count)


def avg_weight_cargo(company):
    conn = Session(bind=engine)
    query = text('select avg(weight_cargo::numeric) '
                 'from public.cargo '
                 'join public.suppliers on public.suppliers.id_supplier = public.cargo.id_supplier '
                 'where name_supplier = :company').bindparams(company=company)
    avg_val = conn.execute(query).fetchone()[0]
    conn.close()
    print('Average weight: {}'.format(avg_val))


def show_trips():
    conn = Session(bind=engine)
    query = text('select * from trip')

    trips = conn.execute(query).fetchall()
    conn.close()
    for trip in trips:
        print("{from_place} - {to_place} {date_from} - {date_to}".format(from_place=trip[1], to_place=trip[2],
                                                                         date_from=trip[3], date_to=trip[4]))


def show_supplier_family(id_supplier):
    conn = Session(bind=engine)
    query = text('select * from recurs_family(:id_supplier)').bindparams(id_supplier=id_supplier)
    row = conn.execute(query)
    for ids in row:
        print(ids[2])
    conn.close()

# Analogs of disconnected objects
def cargo_lighter_than(value):
    """Грузы с весом меньше"""
    conn = Session(bind=engine)
    data = conn.query(Cargo).filter(text('weight_cargo::numeric < :value')).params(value=value).all()
    conn.close()

    for ticket in data:
        print(ticket)


def lightest_cargo():
    """Самый дешевый билет"""
    conn = Session(bind=engine)
    lightest = conn.query(Cargo).order_by(Cargo.weight_cargo).first()
    conn.close()
    print(lightest)


def is_company_exist(name):
    """Существует ли компания с именем name"""
    conn = Session(bind=engine)
    companies = conn.query(Customer).filter(Customer.name_customer == name).all()
    conn.close()
    answer = 'Yes' if companies else 'No'
    print(answer)


def add_company(id, name, city, index):
    """Добавление компании"""
    conn = Session(bind=engine)
    conn.add(Customer(id, name, city, index))
    conn.commit()
    conn.close()


def update_company_name(id, name):
    """Изменить имя компании с id равным id_customer на name"""
    conn = Session(bind=engine)
    company = conn.query(Customer).filter(Customer.id_customer == id).first()
    company.name_customer = name
    conn.commit()
    conn.close()


def show_menu():
    menu = 'Действия с отсоединенными объектами: \n' \
           '\t1. Информация о подключении к БД\n' \
           '\t2. Количество компаний-заказчиков в БД\n' \
           '\t3. Средняей вес посылок заданной компании\n' \
           '\t4. Показать все рейсы\n' \
           '\t5. Список дочерних компаний\n' \
           'Действия с подсоединенными объектами: \n' \
           '\t6. Грузы легче заданного веса\n' \
           '\t7. Самый лёгкий груз\n' \
           '\t8. Существует ли компания с заданным именем\n' \
           '\t9. Добавить компанию\n' \
           '\t10. Изменить имя компании\n' \
           '11. Выход'
    print(menu)

    try:
        act = int(input('Введите действие: '))
        while act < 1 or act > 11:
            print(menu)
            print('Неверное действие')
            act = int(input('Введите действие: '))
    except ValueError:
        print('Неверное действие')
        act = show_menu()

    return act


def get_int(prompt):
    try:
        val = int(input(prompt))
        while val < 0:
            print('Нужно ввести целое неотрицательное число')
            val = int(input(prompt))
    except ValueError:
        print('Нужно ввести целое положительно число')
        val = get_int(prompt)

    return val


def check_id(id):
    conn = Session(bind=engine)
    tmp = conn.query(Customer).filter(text('id_customer = :id')).params(id=id).all()
    conn.close()
    answer = False if tmp else True
    return answer

def get_passenger_data():
    flag = True
    id = None
    while (flag):
        try:
            id = int(input('Введите id: '))
            if id > 0 and check_id(id):
                flag = False
            else:
                continue
        except ValueError:
            continue
    name = input('Введите название компании: ')
    city = input('Введите название города: ')
    index = input('Введите индекс: ')

    return id, name, city, index


def action(act):
    if act == 1:
        engine_info()
    elif act == 2:
        count_customers()
    elif act == 3:
        company = input('Введите название компании: ')
        avg_weight_cargo(company)
    elif act == 4:
        show_trips()
    elif act == 5:
        id_supplier = input('Введите id компании: ')
        show_supplier_family(id_supplier)
    elif act == 6:
        val = get_int('Введите цену: ')
        cargo_lighter_than(val)
    elif act == 7:
        lightest_cargo()
    elif act == 8:
        name = input('Введите имя: ')
        is_company_exist(name)
    elif act == 9:
        id, name, city, index = get_passenger_data()
        add_company(id, name, city, index)
    elif act == 10:
        id_customer = get_int('Введите id компании: ')
        name = input('Введите новое название компании: ')
        update_company_name(id_customer, name)

    print()


if __name__ == '__main__':
    while True:
        inp = show_menu()
        if inp == 11:
            break
        action(inp)