from PyQt5 import QtWidgets
from interface.message import *
from interface.interfaceWindow import *
import sources.checker as checker
import sources.config as config
import sources.function as function


class MyWin(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.ui.pushButtonChangeTable.clicked.connect(self.pushButtonChangeTable)
        self.ui.pushButtonShowTable.clicked.connect(self.pushButtonShowTable)
        self.ui.pushButtonFindResult.clicked.connect(self.pushButtonFindResult)

    def pushButtonChangeTable(self):
        start_x = self.ui.lineEditStartX.text()
        end_x = self.ui.lineEditEndX.text()
        step_x = self.ui.lineEditStepX.text()
        start_y = self.ui.lineEditStartY.text()
        end_y = self.ui.lineEditEndY.text()
        step_y = self.ui.lineEditStepY.text()
        file = open(config.TABLENAME, 'w')
        if not self.ui.checkBoxMulti.isChecked() and checker.strIsFloatOrInt(start_x) \
                and checker.strIsFloatOrInt(end_x) and checker.strIsFloatOrInt(step_x):
            start_x = float(start_x)
            end_x = float(end_x)
            step_x = float(step_x)
            values = function.makeTable([start_x, end_x, step_x])
            for value in values:
                file.write(str(value[0][0]) + '\t' + str(round(value[1], config.EPS)) + '\n')
        elif self.ui.checkBoxMulti.isChecked() and checker.strIsFloatOrInt(start_x) \
                and checker.strIsFloatOrInt(end_x) and checker.strIsFloatOrInt(step_x) \
                and checker.strIsFloatOrInt(start_y) and checker.strIsFloatOrInt(end_y) \
                and checker.strIsFloatOrInt(step_y):
            start_x = float(start_x)
            end_x = float(end_x)
            step_x = float(step_x)
            start_y = float(start_y)
            end_y = float(end_y)
            step_y = float(step_y)
            values = function.makeTableMulti([start_x, end_x, step_x],
                                             [start_y, end_y, step_y])
            for value in values:
                file.write(str(value[0][0]) + '\t' +
                           str(value[1][0]) + '\t' +
                           str(round(value[2], config.EPS)) + '\n')
        else:
            showError(config.err2)
            return None

        file.close()

    def pushButtonShowTable(self):
        if not self.ui.checkBoxMulti.isChecked():
            values = function.getValuesFromFile()
        else:
            values = function.getValuesFromFileMulti()
        if values == None:
            return None
        elif values == []:
            showError(config.err2)
            return None
        text = ""
        if not self.ui.checkBoxMulti.isChecked():
            for value in values:
                text += str(value[0][1]) + '\t' + str(value[1]) + '\n'
        elif self.ui.checkBoxMulti.isChecked():
            for value in values:
                text += str(value[0][1]) + '\t' + str(value[1][1]) + '\t' + str(value[2]) + '\n'

        self.ui.textEdit.clear()
        self.ui.textEdit.append(text)

    def pushButtonFindResult(self):
        if self.ui.radioButtonNewton.isChecked():
            self.findNewtonResult()
        elif self.ui.radioButtonSpline.isChecked():
            self.findSplineResult()
        elif self.ui.radioButtonMulti.isChecked():
            self.findMultiResult()

    def findNewtonResult(self):
        valueN = self.ui.lineEditNX.text()
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
        result = function.interpolateSpline(x, y, valueX)

        self.ui.textEditResult.setText('')
        self.ui.textEditResult.append(str(round(result, config.EPS)))
        self.ui.textEditRightResult.setText('')
        self.ui.textEditRightResult.append(str(round(function.func(valueX), config.EPS)))

    def findMultiResult(self):
        valueX = self.ui.lineEditX.text()
        valueY = self.ui.lineEditY.text()
        nx = self.ui.lineEditNX.text()
        ny = self.ui.lineEditNY.text()

        if checker.strIsInt(nx) and checker.strIsInt(ny) and \
                checker.strIsFloatOrInt(valueX) and checker.strIsFloatOrInt(valueY):
            nx = int(nx)
            ny = int(ny)
            valueX = float(valueX)
            valueY = float(valueY)
        else:
            showError(config.err2)
            return None

        if nx < 0 or ny < 0:
            showError(config.err3)
            return None

        try:
            x_beg = float(self.ui.lineEditStartX.text())
            y_beg = float(self.ui.lineEditStartY.text())
            x_h = float(self.ui.lineEditStepX.text())
            y_h = float(self.ui.lineEditStepY.text())
            x_end = float(self.ui.lineEditEndX.text())
            y_end = float(self.ui.lineEditEndY.text())
            countX = int((x_end - x_beg) / x_h)
            countY = int((y_end - y_beg) / y_h)
        except:
            showError("Problems with diapason!")
            return None
        x, y, z = function.get_matrix(x_beg, x_h, countX, y_beg, y_h, countY)
        function.print_matrix(x, y, z)

        result = function.multi_interpolation(x, y, z, valueX, valueY, nx, ny)

        self.ui.textEditResult.setText('')
        self.ui.textEditResult.append(str(round(result, config.EPS)))
        self.ui.textEditRightResult.setText('')
        self.ui.textEditRightResult.append(str(round(function.func_multi(valueX, valueY), config.EPS)))
        self.refreshInterface()

    def refreshInterface(self):
        self.update()
        self.repaint()
