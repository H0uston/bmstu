import sources.config as config
import sources.checker as checker
from interface.message import showError
import math

def func(x: float) -> float:
    # return math.cos(math.pi / 2 * x) # TODO: мб округлять?
    #return (x * x * x) + 5
    return math.cos(x) - x


def func_multi(x: float, y: float):
    return x ** 2 + y ** 2


def makeTable(diapason: list) -> list:
    values = []
    value = diapason[0]
    while value < diapason[1]:
        values.append(((value, value), func(value)))
        value += diapason[2]
        value = round(value, 10)
    return values


def makeTableMulti(diapason_x: list, diapason_y: list) -> list:
    values = []
    value_x = diapason_x[0]
    while value_x < diapason_x[1]:
        value_y = diapason_y[0]
        while value_y < diapason_y[1]:
            values.append(((value_x, value_x), (value_y, value_y), func_multi(value_x, value_y)))
            value_y += diapason_y[2]
            value_y = round(value_y, 10)
        value_x += diapason_x[2]
        value_x = round(value_x, 10)
    print(values)
    return values


def newtonFormula(x1: float, x2: float, y1: float, y2: float) -> float:
    if (x1 - x2 == 0): #TODO
        print("inf!")
        return 0
    else:
        return (y1 - y2) / (x1 - x2)


def findPolinom(nodes: list, n: int) -> list: # TODO
    coef = []  # Коэфициенты полинома
    x = []
    for i in range(len(nodes)):
        x.append(nodes[i][0][0])
    values = nodes
    for i in range(1, n + 1):  # До нужной степени полинома
        coef.append(values[0][1])
        result = []
        for j in range(len(values) - 1):  # Применяется формула Ньютона на граничные узлы
            result.append(((values[j][0][0], values[j + 1][0][1]), newtonFormula(values[j][0][0], values[j + 1][0][1], values[j][1], values[j + 1][1])))
        values = result
    coef.append(values[0][1])
    # print(coef)
    return [coef, x]


def getValuesFromFile() -> list or None:
    try:
        file = open(config.TABLENAME, 'r')
    except:
        showError(config.err1)
        return None
    text = file.read()
    text = text.split('\n')
    values = []
    for line in text:
        if line == '':
            continue
        tmp = line.split('\t')
        if len(tmp) == 2 and checker.strIsFloatOrInt(tmp[0]) and checker.strIsFloatOrInt(tmp[1]):
            values.append(((float(tmp[0]), float(tmp[0])), float(tmp[1])))
        else:
            showError(config.err2)
            return None
    try:
        file.close()
    except:
        pass
    return values


def getValuesFromFileMulti() -> list or None:
    try:
        file = open(config.TABLENAME, 'r')
    except:
        showError(config.err1)
        return None
    text = file.read()
    text = text.split('\n')
    values = []
    for line in text:
        if line == '':
            continue
        tmp = line.split('\t')
        if (len(tmp) == 3 and checker.strIsFloatOrInt(tmp[0]) and checker.strIsFloatOrInt(tmp[1])
                and checker.strIsFloatOrInt(tmp[2])):
            values.append(((float(tmp[0]), float(tmp[0])),
                           (float(tmp[1]), float(tmp[1])), float(tmp[2])))
        else:
            showError(config.err2)
    try:
        file.close()
    except:
        pass
    return values


def findCenter(values: list, x:float) -> float or None:
    diapason = [values[0][0][0], values[len(values) - 1][0][0]]  # Диапазон значений
    currValue = diapason[0]  # Текущие значение
    number = 0
    for i in range(len(values) - 1):
        if values[i][0][0] <= x <= values[i + 1][0][0]:
            if x >= ((values[i + 1][0][0] + values[i][0][0]) / 2):
                center = values[i + 1][0][0]
                print(center)
                return i + 1
            elif x < ((values[i + 1][0][0] + values[i][0][0]) / 2):
                center = values[i][0][0]
                return i
            else:
                print("Hey buddy, I think you've got the wrong door, the leather club's two blocks down.")
                return None  # TODO: Может произойти?
    return None


def findValue(polynomial: list, x: float) -> float or None:  #TODO
    result = polynomial[0][0]
    for i in range(1, len(polynomial[0])):
        tmp = 1
        for j in range(i):
            tmp *= (x - polynomial[1][j])
        result += polynomial[0][i] * tmp
    return result


def print_matrix(x, y, z):
    print("   y\\x ", end='')
    for i in x:
        print("{:6}".format(i), end=' ')

    for i in range(len(y)):
        print("\n{:6}".format(y[i]), end=' ')
        for j in z[i]:
            print("{:6}".format(j), end=' ')
    print('\n')

def formNodes(values: list, valuesCenter: int, n: int) -> list:
    sides = [0, 0]  # 0-вой элемент - кол-во левых точек от цента, 1-ый элемент - кол-во правых точек от центра
    result = [''] * (2 * n + 1)
    resultCenter = len(result) // 2
    result[resultCenter] = values[valuesCenter]
    for i in range(1, n + 1):
        if sides[1] <= sides[0] and (valuesCenter + sides[1] + 1) < len(values):
            sides[1] += 1
            result[resultCenter + sides[1]] = values[valuesCenter + sides[1]]
        elif (valuesCenter - sides[0] - 1) >= 0:
            sides[0] += 1
            result[resultCenter - sides[0]] = values[valuesCenter - sides[0]]
        elif (valuesCenter + sides[1] + 1) < len(values):
            sides[1] += 1
            result[resultCenter + sides[1]] = values[valuesCenter + sides[1]]
        else:
            print("Hey buddy, I think you've got the wrong door, the leather club's two blocks down.")
            assert(0)

    # Удаляем все лишние элементы
    count = result.count('')
    for i in range(count):
        result.pop(result.index(''))

    return result


def interpolateSpline(x, y, x_value):
    n = len(x)
    i_near = min(range(n), key=lambda i: abs(x[i] - x_value))

    h = [0 if not i else x[i] - x[i - 1] for i in range(n)]

    A = [0 if i < 2 else h[i - 1] for i in range(n)]
    B = [0 if i < 2 else -2 * (h[i - 1] + h[i]) for i in range(n)]
    D = [0 if i < 2 else h[i] for i in range(n)]
    F = [0 if i < 2 else -3 * ((y[i] - y[i - 1]) / h[i] - (y[i - 1] - y[i - 2]) / h[i - 1]) for i in range(n)]

    ksi = [0 for i in range(n + 1)]
    eta = [0 for i in range(n + 1)]
    for i in range(2, n):
        ksi[i + 1] = D[i] / (B[i] - A[i] * ksi[i])
        eta[i + 1] = (A[i] * eta[i] + F[i]) / (B[i] - A[i] * ksi[i])

    c = [0 for i in range(n + 1)]
    for i in range(n - 2, -1, -1):
        c[i] = ksi[i + 1] * c[i + 1] + eta[i + 1]

    a = [0 if i < 1 else y[i - 1] for i in range(n)]
    b = [0 if i < 1 else (y[i] - y[i - 1]) / h[i] - h[i] / 3 * (c[i + 1] + 2 * c[i]) for i in range(n)]
    d = [0 if i < 1 else (c[i + 1] - c[i]) / (3 * h[i]) for i in range(n)]

    return a[i_near] + b[i_near] * (x_value - x[i_near - 1]) + c[i_near] * \
           ((x_value - x[i_near - 1]) ** 2) + d[i_near] * ((x_value - x[i_near - 1]) ** 3)


def get_matrix(x_beg, x_h, x_n, y_beg, y_h, y_n):
    x = [x_beg + i * x_h for i in range(x_n)]
    y = [y_beg + i * y_h for i in range(y_n)]
    z = [[func_multi(i, j) for i in x] for j in y]
    return x, y, z


# Choose n dots nearest to x in a
def choose_dots(a, n, x):
    a_len = len(a)
    i_near = min(range(a_len), key=lambda i: abs(a[i] - x))  # index of nearest value
    space_needed = math.ceil(n / 2)

    if (i_near + space_needed + 1 > a_len):
        i_end = a_len
        i_start = a_len - n
    elif (i_near < space_needed):
        i_start = 0
        i_end = n
    else:
        i_start = i_near - space_needed + 1
        i_end = i_start + n

    return i_start, i_end


# Matrix of differences
def get_diff_matr(tbl, n):
    for i in range(n):
        tmp = []
        for j in range(n - i):
            tmp.append((tbl[i + 1][j] - tbl[i + 1][j + 1]) / (tbl[0][j] - tbl[0][i + j + 1]))
        tbl.append(tmp)
    return tbl


# n - polynom's power
def newtons_interpolation(tbl, n, x):
    matr = get_diff_matr(tbl, n)
    tmp = 1
    res = 0
    print(matr)
    for i in range(n + 1):
        res += tmp * matr[i + 1][0]
        tmp *= (x - matr[0][i])
    return res


def multi_interpolation(x, y, z, x_val, y_val, x_n, y_n):
    ix_beg, ix_end = choose_dots(x, x_n + 1, x_val)
    iy_beg, iy_end = choose_dots(y, y_n + 1, y_val)
    x = x[ix_beg: ix_end]
    y = y[iy_beg: iy_end]
    z = z[iy_beg: iy_end]
    print('x: ', x, '\n', 'y: ', y, '\n', 'z: ', z, '\n')
    for i in range(y_n + 1):
        z[i] = z[i][ix_beg: ix_end]
    print('final z: ', z)
    res = [newtons_interpolation([x, z[i]], x_n, x_val) for i in range(y_n + 1)]
    print('res: ', res)
    return newtons_interpolation([y, res], y_n, y_val)
