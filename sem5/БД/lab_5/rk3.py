import psycopg2
import datetime
import copy

con = psycopg2.connect(
        database='rk3',
        user='postgres',
        password='admin',
        host='localhost'
    )

# Найти отделы, в которых хоть один сотрудник опаздывает больше 3-х раз в неделю.
def first_task():
    cur = con.cursor()
    cur.execute("select * from employee")
    employees = cur.fetchall()
    cur.execute("select * from timenote")
    timenote = cur.fetchall()
    t = []

    for line1 in employees:
        for line2 in timenote:
            if line1[0] == line2[0]:
                t.append((line1[0], line1[1], line1[2], line1[3], line2[1], line2[2],
                          line2[3], line2[4]))
    dep = {}
    staff = {}
    for i in range(len(t)):
        dep[t[i][3]] = 0
        staff[t[i][0]] = 0

    for i in range(len(t)):
        if t[i][6] > datetime.time(9, 0) and t[i][-1] == 1:
            staff[t[i][0]] += 1
        if staff[t[i][0]] > 3:
            dep[t[i][3]] += 1
    print('Отделы, с сотрудником, опаздывающим более 3 раз в неделю')
    for i in list(dep.keys()):
        if dep[i] > 0:
            print(i)


def calculate_age(birth_date):
    today = datetime.date.today()
    try:
        birthday = birth_date.replace(year=today.year)
    except ValueError:
        birthday = birth_date.replace(year=today.year,
                                month=birth_date.month + 1, day=1)

    if birthday > today:
        return today.year - birth_date.year - 1
    else:
        return today.year - birth_date.year


# Найти средний возраст сотрудников, не находящихся на рабочем месте 8 часов в день.
def second_task():
    cur = con.cursor()
    cur.execute('SELECT * FROM timenote')
    timenote = cur.fetchall()
    cur.execute('SELECT * FROM employee')
    employees = cur.fetchall()

    empls = dict()
    for employee in employees:
        empls[employee[0]] = False

    for i in range(len(timenote) - 1):
        for j in range(len(timenote) - i - 1):
            if timenote[j][0] > timenote[j + 1][0]:
                timenote[j], timenote[j + 1] = timenote[j + 1], timenote[j]

    for i in range(len(timenote) - 1):
        for j in range(len(timenote) - i - 1):
            if timenote[j][1] > timenote[j + 1][1] and timenote[j][0] == timenote[j + 1][0]:
                timenote[j], timenote[j + 1] = timenote[j + 1], timenote[j]

    for i in range(len(timenote) - 1):
        for j in range(len(timenote) - i - 1):
            if timenote[j][3] > timenote[j + 1][3] and timenote[j][0] == timenote[j + 1][0] and \
                    timenote[j][1] == timenote[j + 1][1]:
                timenote[j], timenote[j + 1] = timenote[j + 1], timenote[j]
    cur_hours = 0
    for i in range(len(timenote)):
        if i < len(timenote) - 1:
            if timenote[i][0] == timenote[i + 1][0] and timenote[i][1] == timenote[i + 1][1] and timenote[i][4] == 1:
                cur_hours += timenote[i+1][3].hour * 60 + timenote[i+1][3].minute - timenote[i][3].hour * 60 - \
                             timenote[i][3].minute
            elif ((timenote[i][0] == timenote[i + 1][0] and timenote[i][1] != timenote[i + 1][1]) or
                  timenote[i][0] != timenote[i + 1][0]) and timenote[i][4] == 1:
                cur_hours += 24*60 - timenote[i][3].hour * 60 - timenote[i][3].minute
                if cur_hours < 480:
                    empls[timenote[i][0]] = True
                cur_hours = 0
            elif timenote[i][0] != timenote[i + 1][0] or (timenote[i][1] != timenote[i + 1][1] and timenote[i][4] == 2):
                if cur_hours < 480:
                    empls[timenote[i][0]] = True
                cur_hours = 0
        elif timenote[i][4] == 1:
            cur_hours += 24 * 60 - timenote[i][3].hour * 60 - timenote[i][3].minute
            if cur_hours < 480:
                empls[timenote[i][0]] = True
            cur_hours = 0
    sum_age = 0
    cnt = 0
    for empl, key in empls.items():
        if key:
            sum_age += calculate_age(employees[empl - 1][2])
            cnt += 1
    if cnt > 0:
        print('Средний возраст: ', sum_age / cnt)
    else:
        print('Таких людей нет')


# Вывести все отделы и количество сотрудников хоть раз опоздавших за всю историю учета.
def third_task():
    cur = con.cursor()
    cur.execute('SELECT * FROM timenote')
    timenote = cur.fetchall()
    cur.execute('SELECT * FROM employee')
    employees = cur.fetchall()
    deps = dict()
    empls = dict()
    empls_late = dict()
    for employee in employees:
        deps[employee[3]] = 0
        empls[employee[0]] = datetime.time(23, 59)
        empls_late[employee[0]] = 0
    dates = dict()
    for sch in timenote:
        dates[sch[1]] = copy.copy(empls)

    for sch in timenote:
        if sch[3] < dates[sch[1]][sch[0]]:
            dates[sch[1]][sch[0]] = sch[3]
    for dt, els in dates.items():
        for em, time in els.items():
            if time > datetime.time(9, 0):
                empls_late[em] += 1
    for emp, cnt in empls_late.items():
        if cnt > 0:
            deps[employees[emp - 1][3]] += 1
    print('Отделы и число опоздавших')
    for title, cnt in deps.items():
        print(title,'-',cnt)


def third_task_sql():
    cur = con.cursor()
    cur.execute('''
    select count(tmp2.em), department
    from (
    	select e.employee_id as em, e.department as e_d
    	from (
    		select employee_id, come_date, min(come_time) as first_entry
    		from timenote
    		where var = 1
    		group by employee_id, come_date
    	) as tmp inner join employee e on e.employee_id = tmp.employee_id
        where first_entry > '9:00'
        group by e.employee_id
    ) as tmp2 right join employee e on tmp2.e_d = e.department
    group by e.department
    ''')
    print('Отделы и число опоздавших')
    for row in cur:
        print(row[1], '-', row[0])


if __name__ == '__main__':
    third_task_sql()
    third_task()
    first_task()
    second_task()

con.close()