# Градов Владимир Михаилович (502л)
# Первая лабораторная
# Аппроксимация функций (интерполяция полиномом Ньютона)
# x | y = cos(grad(90)*x)| y(x0,x1)| y(x0, x1, x2)| y(x0, x1, x2, x3| y(x0, x1, ..., x4)|
# _______________________|_________|________________________________|___________________|
#  0    | 1              | -0.304  | -1.128       | 0,382           | 0,149
#  0.25 | 0.924          | -0.868  | -0.856       | 0,512           |
#  0.5  | 0.707          | -1.296  | -0.472
#  0.75 | 0.383          | -1.532  |
#  1    | 0              |         |
#
# Result: y(x) = 1 - 0.304(x - 0) - 1.128 * x * (x - 0.25) + 0.382 * x * (x - 0.25) * (x - 0.5) + 0.149 * x * (x - 0.25) * (x - 0.5) * ( x - 0.75)
#
#
#
#
# We have: 1. table (функция дана, с шагом диапазона)
#          2. n > 0 (степень полинома)
#          3. x
#
# Result: y(x)
#
# Example:
# y(0.6) == 0.589
# y(0.6) == 0.588 (полином 4-ой степени)
#
#
# 2-я часть
# применить разработанную программу к поиску корня функции
#
# Example:
# f(x) = cos(x) - x
#
import math
import sys
from PyQt5 import QtCore, QtGui, QtWidgets
from interface.interfaceWindow import *
from interface.message import *
import config
import checker
import function
from interface.mainWindow import MyWin


def main():
    diapason = [-10, 26, 5]
    values = function.makeTable(diapason)

    x = 5.4
    numberCenter = function.findCenter(diapason, x)
    print(numberCenter)
    n = 0
    if n > len(values) or numberCenter == None or numberCenter < 0:
        print("Extrapolyazia!")
        return None

    nodes = function.formNodes(values, numberCenter, n)
    polynomial = function.findPolinom(nodes, n)
    print(polynomial)
    result = function.findValue(polynomial, x)
    print(result)



if __name__ == "__main__":
    if False:
        main()
    else:
        app = QtWidgets.QApplication(sys.argv)
        myapp = MyWin()
        myapp.show()
        sys.exit(app.exec_())
