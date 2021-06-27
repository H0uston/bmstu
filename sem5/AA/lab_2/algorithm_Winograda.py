

def matrix_multiplication_winograd(matrix_a: list, matrix_b: list) -> list:
    a = len(matrix_a)
    b = len(matrix_b)
    c = len(matrix_b[0])

    if b != len(matrix_a[0]):
        print("Different sizes!")
        return []

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

    # For odd matrix
    if b % 2:
        for i in range(a):
            for j in range(c):
                res[i][j] += matrix_a[i][b - 1] * matrix_b[b - 1][j]

    return res


def matrix_multiplication_improved_winograd(matrix_a: list, matrix_b: list) -> list:
    a = len(matrix_a)
    b = len(matrix_b)
    c = len(matrix_b[0])

    if b != len(matrix_a[0]):
        print("Different dimension of the matrics")
        return []

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

    # For odd matrix
    if b % 2:
        for i in range(a):
            for j in range(c):
                res[i][j] = sum(matrix_a[i][b - 1] * matrix_b[b - 1][j])

    return res
