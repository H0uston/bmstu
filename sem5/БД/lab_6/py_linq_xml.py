from py_linq import Enumerable
import dict2xml
from bs4 import BeautifulSoup


def get_table(file_name):
    with open(file_name) as f:
        soup = BeautifulSoup(f, 'xml')

    rows = soup.find_all('row')
    res = []
    for row in rows:
        row_dict = {}
        for child in row:
            tmp = str(child)
            if tmp.find('\\n') != -1:
                continue
            try:
                row_dict.update({child.name: child.text})
            except:
                continue
        res.append(row_dict)

    return res


def get_count(table):
    return Enumerable(table).count()


def dict_to_row(row_dict):
    xml_title = 'row'
    xml_body = [dict2xml.dict2xml({attr: row_dict[attr]}) for attr in row_dict]
    return '<{0}>{1}</{0}>'.format(xml_title, ''.join(xml_body))


def add_supplier(file_name, supplier):
    with open(file_name) as f:
        soup = BeautifulSoup(f, 'xml')

    raw_row = dict_to_row(supplier)
    row = BeautifulSoup(raw_row, 'xml')

    soup.suppliers.append(row)
    with open(file_name, 'w') as f:
        f.write(soup.prettify())


def replace_supplier(file_name):
    with open(file_name) as f:
        soup = BeautifulSoup(f, 'xml')

    soup.row.city_supplier.string = 'Omsk'

    with open(file_name, 'w') as f:
        f.write(soup.prettify())


if __name__ == '__main__':
    file_name = 'suppliers_data.xml'
    table = get_table(file_name)
    print(table)
    print(get_count(table))
    add_supplier(
        file_name,
        {'id_supplier': 1002, 'name_supplier': 'name', 'city_supplier': 'Vyborg', 'sector_supplier': 'Finance'}
    )
    replace_supplier(file_name)