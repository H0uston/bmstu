from datetime import datetime
from pony.orm import *

db = Database()


class Customers(db.Entity):
    _table_ = ("public", "customers")
    id_customer = PrimaryKey(int, auto=True)
    name_customer = Required(str)
    city_customer = Required(str)
    index_customer = Required(int)
    customer = Set(lambda: Cargo, reverse="id_customer")


class Suppliers(db.Entity):
    _table_ = ("public", "suppliers")
    id_supplier = PrimaryKey(int, auto=True)
    name_supplier = Required(str)
    city_supplier = Required(str)
    sector_supplier = Required(str)
    owner = Required(str)
    supplier = Set(lambda: Cargo, reverse="id_supplier")


class Trip(db.Entity):
    _table_ = ("public", "trip")
    id_trip = PrimaryKey(int, auto=True)
    from_trip = Required(str)
    to_trip = Required(str)
    start_date_trip = Required(str)
    end_data_trip = Required(str)
    trip = Set(lambda: Cargo, reverse="id_trip")


class Cargo(db.Entity):
    _table_ = ("public", "cargo")
    id_customer = Required(Customers, reverse="customer")
    id_supplier = Required(Suppliers, reverse="supplier")
    id_trip = Required(Trip, reverse="trip")
    PrimaryKey(id_customer, id_supplier, id_trip)
    weight_cargo = Required(float)


db.bind(
    provider='postgres',
    database='transportation',
    host='localhost',
    port='5433',
    user='houston',
    password='admin'
)
db.generate_mapping()


@db_session
def get_company_by_name(name_customer):
    """
    :param name_customer: имя компании заказчика
    :return: все компании заказчики с именем name_customer
    """
    # noinspection PyTypeChecker
    return select((p.id_customer, p.name_customer, p.city_customer, p.index_customer) for p in Customers
                  if name_customer in p.name_customer).fetch()


@db_session
def get_suppliers_by_city(city_supplier):
    """
    :param : id пассажира
    :return: все билеты пассажира
    """
    # noinspection PyTypeChecker
    return select((p.id_supplier, p.name_supplier, p.city_supplier) for p in Suppliers
                  if city_supplier in p.city_supplier).fetch()


@db_session
def insert_customer(id_customer, name_customer, city_customer, index_customer):
    """
    Добавление компании-заказчика
    :param id_customer: id заказчика
    :param name_customer: название компании заказчика
    :param city_customer: город заказчика
    :param index_customer: индекс офиса заказчика
    :return: id созданной компании-заказчика
    """
    p = Customers(id_customer=id_customer, name_customer=name_customer, city_customer=city_customer, index_customer=index_customer)
    commit()
    return p.id_customer


@db_session
def change_index(id_customer, new_index):
    """
    Изменение индекса компании заказчика
    :param id_customer: id заказчика
    :param new_index: новый индекс заказчика
    """
    customer = Customers[id_customer]
    customer.index_customer = new_index


@db_session
def delete_customer(id_customer):
    """
    Удаление компании-заказчика
    :param id_customer: id компании-заказчика
    """
    Customers[id_customer].delete()


@db_session
def get_suppliers_cargo(id_company):
    """
    Получение всех грузов поставщиков
    :param id_company: id поставщика
    :return: список грузов
    """
    return Cargo.select_by_sql(
        'select * from Cargo \
         WHERE $(id_company) = id_supplier'
    )


if __name__ == '__main__':
    print(get_company_by_name('Biostage, Inc.'))
    print(get_suppliers_by_city('Moscow'))
    #new_id = insert_customer(300, 'KKK', "Florida", 57343)
    #print(new_id)
    change_index(100, 222222)
    #delete_customer(300)
    print(get_suppliers_cargo(15))
