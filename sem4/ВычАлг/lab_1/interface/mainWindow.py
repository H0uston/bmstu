from PyQt5 import QtWidgets
from interface.message import *
from interface.interfaceWindow import *
import checker
import config
import function


class MyWin(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.ui.pushButtonChangeTable.clicked.connect(self.pushButtonChangeTable)
        self.ui.pushButtonShowTable.clicked.connect(self.pushButtonShowTable)
        self.ui.pushButtonFindResult.clicked.connect(self.pushButtonFindResult)
        self.ui.pushButtonFindRoots.clicked.connect(self.pushButtonFindRoots)

    def pushButtonChangeTable(self):
        start = self.ui.lineEditStart.text()
        end = self.ui.lineEditEnd.text()
        step = self.ui.lineEditStep.text()
        if checker.strIsFloatOrInt(start) and checker.strIsFloatOrInt(end) and checker.strIsFloatOrInt(step):
            start = float(start)
            end = float(end)
            step = float(step)
        else:
            showError(config.err2)
            return None
        values = function.makeTable([start, end, step])
        file = open(config.TABLENAME, 'w')
        for value in values:
            file.write(str(value[0][0]) + '\t' + str(round(value[1], config.EPS)) + '\n')
        file.close()

    def pushButtonShowTable(self):
        values = function.getValuesFromFile()
        if values == None:
            return None
        elif values == []:
            showError(config.err2)
            return None
        text = ""
        for value in values:
            text += str(value[0][1]) + '\t' + str(value[1]) + '\n'

        self.ui.textEdit.clear()
        self.ui.textEdit.append(text)

    def pushButtonFindResult(self):
        valueN = self.ui.lineEditN.text()
        valueX = self.ui.lineEditX.text()
        if checker.strIsInt(valueN) and checker.strIsFloatOrInt(valueX):
            valueN = int(valueN)
            valueX = float(valueX)
        else:
            showError(config.err2)
            return None

        if valueN < 0:
            showError(config.err3)
            return None

        values = function.getValuesFromFile()
        if values == None:
            showError(config.err1)
            return None

        numberCenter = function.findCenter(values, valueX) # TODO
        if numberCenter == None:
            showError(config.err4)
            return None
        nodes = function.formNodes(values, numberCenter, valueN)
        polynomial = function.findPolinom(nodes, valueN)
        result = function.findValue(polynomial, valueX)
        self.ui.textEditResult.setText('')
        self.ui.textEditResult.append(str(round(result, config.EPS)))
        self.ui.textEditRightResult.setText('')
        self.ui.textEditRightResult.append(str(round(function.func(valueX), config.EPS)))


    def pushButtonFindRoots(self):
        try:
            valueN = int(self.ui.lineEditN.text())
        except:
            valueN = None
        values = function.getValuesFromFile()
        x = []
        y = []
        for value in values:
            x.append(value[0][0])
            y.append(value[1])
        assert(len(x) == len(y))

        """
        dictionary = {y[i]: x[i] for i in range(len(x))}
        from collections import OrderedDict
        dictionary = OrderedDict(sorted(dictionary.items(), key=lambda t: t[0]))
        x = []
        y = []
        for node in dictionary:
            x.append(dictionary[node])
            y.append(node)
        print(x)
        print(y)
        """

        newValues = ['' for i in range(len(x))]
        for i in range(len(x)):
            newValues[i] = ((y[i], y[i]), x[i])
        # print(newValues)
        if valueN == None:
            valueN = len(newValues) - 1
        polynomial = function.findPolinom(newValues, valueN)
        result = function.findValue(polynomial, 0)
        self.ui.textEditResult.setText('')
        self.ui.textEditRoot.setText(str(round(result, config.EPS)))