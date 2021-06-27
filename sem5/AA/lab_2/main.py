from time import time
from random import randint


def print_matrix(matrix: list) -> None:
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            print("{:5d}".format(matrix[i][j]), end=" ")
        print()


def create_random_matrix(n: int, m: int, max_elem: int) -> list:
    matrix = [[randint(0, max_elem) for _ in range(n)] for _ in range(m)]
    return matrix


def matrix_multiplication(matrix_a: list, matrix_b: list) -> list:
    if len(matrix_b) != len(matrix_a[0]):
        print("Different sizes!")
        return []

    res = [[0 for _ in range(len(matrix_b[0]))] for _ in range(len(matrix_a))]

    for i in range(len(matrix_a)):
        for j in range(len(matrix_a[0])):
            for k in range(len(matrix_b[0])):
                res[i][k] = res[i][k] + matrix_a[i][j] * matrix_b[j][k]
    return res


def matrix_multiplication_winograd(matrix_a: list, matrix_b: list) -> list:
    b = len(matrix_b)
    if b != len(matrix_a[0]):
        print("Different sizes!")
        return []

    a = len(matrix_a)
    c = len(matrix_b[0])

    d = b // 2
    row_factor = [0 for _ in range(a)]
    col_factor = [0 for _ in range(c)]

    # Row Factor calc
    for i in range(a):
        for j in range(d):
            row_factor[i] += matrix_a[i][2 * j] * matrix_a[i][2 * j + 1]

    # Col Factor calc
    for i in range(c):
        for j in range(d):
            col_factor[i] += matrix_b[2 * j][i] * matrix_b[2 * j + 1][i]

    res = [[0 for _ in range(c)] for _ in range(a)]
    for i in range(a):
        for j in range(c):
            res[i][j] = - row_factor[i] - col_factor[j]
            for k in range(d):
                res[i][j] += ((matrix_a[i][2 * k] + matrix_b[2 * k + 1][j]) *
                              (matrix_a[i][2 * k + 1] + matrix_b[2 * k][j]))

    if b % 2:
        for i in range(a):
            for j in range(c):
                res[i][j] += matrix_a[i][b - 1] * matrix_b[b - 1][j]

    return res


def matrix_multiplication_improved_winograd(matrix_a: list, matrix_b: list) -> list:
    b = len(matrix_b)

    if b != len(matrix_a[0]):
        print("Different dimension of the matrics")
        return []

    a = len(matrix_a)
    c = len(matrix_b[0])

    d = b // 2

    row_factor = [0 for _ in range(a)]
    col_factor = [0 for _ in range(c)]

    # Row Factor calc
    for i in range(a):
        row_factor[i] = sum(matrix_a[i][2 * j] * matrix_a[i][2 * j + 1] for j in range(d))

    # Col Factor calc
    for i in range(c):
        col_factor[i] = sum(matrix_b[2 * j][i] * matrix_b[2 * j + 1][i] for j in range(d))

    res = [[0 for _ in range(c)] for j in range(a)]
    for i in range(a):
        for j in range(c):
            res[i][j] = sum((matrix_a[i][2 * k] + matrix_b[2 * k + 1][j]) *
                               (matrix_a[i][2 * k + 1] + matrix_b[2 * k][j]) for k in range(d)) \
                            - row_factor[i] - col_factor[j]

    if b % 2:
        for i in range(a):
            for j in range(c):
                res[i][j] = sum(matrix_a[i][b - 1] * matrix_b[b - 1][j])

    return res

def create_random_matrix(n: int, m: int, max_elem: int) -> list:
    matrix = [[randint(0, max_elem) for _ in range(n)] for _ in range(m)]
    return matrix


def countingSort(array, place):
    size = len(array)
    output = [0] * size
    count = [0] * 10
    for i in range(0, size):
        index = array[i] // place
        count[index % 10] += 1
    for i in range(1, 10):
        count[i] += count[i - 1]
    i = size - 1
    while i >= 0:
        index = array[i] // place
        output[count[index % 10] - 1] = array[i]
        count[index % 10] -= 1
        i -= 1
    for i in range(0, size):
        array[i] = output[i]


def radixSort(array):
    max_element = max(array)
    place = 1
    while max_element // place > 0:
        countingSort(array, place)
        place *= 10

if __name__ == "__main__":
    data = [randint(0, 1000) for _ in range(10)]
    radixSort(data)
    print(data)




