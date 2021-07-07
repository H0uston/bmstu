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
        if self.ui.radioButtonNewton.isChecked():
            self.findNewtonResult()
        elif self.ui.radioButtonSpline.isChecked():
            self.findSplineResult()


    def findNewtonResult(self):
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

        numberCenter = function.findCenter(values, valueX)
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

    def findSplineResult(self):
        valueX = self.ui.lineEditX.text()
        if checker.strIsFloatOrInt(valueX):
            valueX = float(valueX)
        else:
            showError(config.err2)
            return None

        values = function.getValuesFromFile()
        if values == None:
            showError(config.err1)
            return None

        x = []
        y = []
        for i in range(len(values)):
            x.append(values[i][0][0])
            y.append(values[i][1])
        result = function.interpolate(x, y, valueX)

        self.ui.textEditResult.setText('')
        self.ui.textEditResult.append(str(round(result, config.EPS)))
        self.ui.textEditRightResult.setText('')
        self.ui.textEditRightResult.append(str(round(function.func(valueX), config.EPS)))