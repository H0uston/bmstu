import math

import numpy as np


def matrix_full_plan():
    res = [[1 for i in range(64)] for j in range(64)]
    step = 1
    for z in range(6):
        sign = -1
        for i in range(64):
            res[i][z + 1] = sign
            if (i + 1) % step == 0:
                sign *= -1
        step *= 2

    for i in range(64):

        iterator = 0
        for z in range(1, 6):
            for e in range(z + 1, 7):
                res[i][7 + iterator] = res[i][z] * res[i][e] 
                iterator += 1
                # if i == 1:
                #     print(" " + str(z) + " : " + str(e))

        for z in range(1, 6):
            for e in range(z + 1, 6):
                for y in range(e + 1, 7):
                    res[i][7 + iterator] = res[i][z] * res[i][e] * res[i][y]
                    iterator += 1
                    # if i == 1:
                    #     print(" " + str(z) + " : " + str(e) + " : " + str(y))
        
        for z in range(1, 6):
            for e in range(z + 1, 6):
                for y in range(e + 1 , 6):
                    for n in range(y + 1, 7):
                        res[i][7 + iterator] = res[i][z] * res[i][e] * res[i][y] * res[i][n]
                        iterator += 1
                        # if i == 1:
                        #     print(" " + str(z) + " : " + str(e) + " : " + str(y) + " : " + str(n))
        
        for z in range(1, 6):
            for e in range(z + 1, 6):
                for y in range(e + 1, 6):
                    for n in range(y + 1, 6):
                        for a in range(n + 1, 7):
                            res[i][7 + iterator] = res[i][z] * res[i][e] * res[i][y] * res[i][n] * res[i][a]
                            iterator += 1
                            # if i == 1:
                            #     print(" " + str(z) + " : " + str(e) + " : " + str(y) + " : " + str(n) + " : " + str(a))
                            
        z = 1
        e = 2
        y = 3
        n = 4
        a = 5
        l = 6
        res[i][7 + iterator] = res[i][z] * res[i][e] * res[i][y] * res[i][n] * res[i][a] * res[i][l]
        iterator += 1
        # if i == 1:
        #     print(" " + str(z) + " : " + str(e) + " : " + str(y) + " : " + str(n) + " : " + str(a) + " : " + str(l))
                            

    return res


def matrix_partial_plan():
    res = [[1 for i in range(32)] for j in range(32)]
    step = 1
    for j in range(5):
        sign = -1
        for i in range(32):
            res[i][j + 1] = sign
            if (i + 1) % step == 0:
                sign *= -1
        step *= 2
    for i in range(32):

        res[i][6] = res[i][1] * res[i][2] * res[i][3] * res[i][4] * res[i][5]

        iterator = 0
        for z in range(1, 6):
            for e in range(z + 1, 7):
                res[i][7 + iterator] = res[i][z] * res[i][e] 
                iterator += 1
                #if i == 1:
                #    print(" " + str(z) + " : " + str(e))

        for z in range(1, 6):
            if z > 1: 
                break
            for e in range(z + 1, 6):
                for y in range(e + 1, 7):
                    res[i][7 + iterator] = res[i][z] * res[i][e] * res[i][y]
                    iterator += 1
                    #if i == 1:
                    #    print(" " + str(z) + " : " + str(e) + " : " + str(y))
    return res


def calc_b_full(plan, y):
    b = list()
    for i in range(len(plan[0])):
        b_cur = 0
        for j in range(len(plan)):
            b_cur += plan[j][i] * y[j]
        b.append(b_cur / len(plan))
    return b


def calc_b_partial(plan, y):
    b = list()
    for i in range(int(np.log2(len(plan))) + 2):
        b_cur = 0
        for j in range(len(plan)):
            b_cur += plan[j][i] * y[j]
        b.append(b_cur / len(plan))
    for i in range(int(np.log2(len(plan))) + 2, len(plan[0])):
        b_cur = 0
        for j in range(len(plan)):
            b_cur += plan[j][i] * y[j]
        b.append(b_cur / len(plan) / 2)
    return b


def calc_y(b, x):
    res = 0
    for i in range(len(b)):
        res += b[i] * x[i]
    return res


def fill_y(plan, b1, b2):
    ylin = list()
    ynlin = list()
    for i in range(len(plan)):
        if len(plan[i]):
            ylin.append(calc_y(b1, plan[i]))
            ynlin.append(calc_y(b2, plan[i]))
    return ylin, ynlin


def fill_plan(plan, y, ylin, ynlin):
    for i in range(len(plan)):
        if len(plan[i]):
            plan[i].append(math.fabs(y[i]))
            plan[i].append(math.fabs(ylin[i]))
            plan[i].append(math.fabs(ynlin[i]))
            plan[i].append(abs(y[i] - ylin[i]))
            plan[i].append(abs(y[i] - ynlin[i]))


def expand_full_plan(plan, custom_plan, y):
    b = calc_b_full(plan, y)

    ylin, ynlin = fill_y(plan, b[:int(np.log2(len(b))) + 1], b)
    fill_plan(plan, y, ylin, ynlin)
    ylin, ynlin = fill_y(custom_plan, b[:int(np.log2(len(b))) + 1], b)
    if len(custom_plan) > 0:
        fill_plan(custom_plan, y, ylin, ynlin)

    return b


def expand_partial_plan(plan, custom_plan, y):
    b = calc_b_partial(plan, y)

    ylin, ynlin = fill_y(plan, b[:int(np.log2(len(b))) + 1], b)
    fill_plan(plan, y, ylin, ynlin)
    ylin, ynlin = fill_y(custom_plan, b[:int(np.log2(len(b))) + 1], b)
    if len(custom_plan) > 0:
        fill_plan(custom_plan, y, ylin, ynlin)

    return b


def scale_factor(x, realmin, realmax, xmin=-1, xmax=1):
    return realmin + (realmax - realmin) * (x - xmin) / (xmax - xmin)
