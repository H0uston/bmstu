# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'interfaceWindow.ui'
#
# Created by: PyQt5 UI code generator 5.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(625, 600)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(MainWindow.sizePolicy().hasHeightForWidth())
        MainWindow.setSizePolicy(sizePolicy)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.layoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.layoutWidget.setGeometry(QtCore.QRect(0, 30, 621, 42))
        self.layoutWidget.setObjectName("layoutWidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.layoutWidget)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.label = QtWidgets.QLabel(self.layoutWidget)
        font = QtGui.QFont()
        font.setFamily("Arial")
        font.setBold(True)
        font.setWeight(75)
        font.setStrikeOut(False)
        self.label.setFont(font)
        self.label.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setObjectName("label")
        self.verticalLayout.addWidget(self.label)
        self.layoutWidget1 = QtWidgets.QWidget(self.centralwidget)
        self.layoutWidget1.setGeometry(QtCore.QRect(50, 110, 221, 411))
        self.layoutWidget1.setObjectName("layoutWidget1")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.layoutWidget1)
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.label_3 = QtWidgets.QLabel(self.layoutWidget1)
        self.label_3.setAlignment(QtCore.Qt.AlignCenter)
        self.label_3.setObjectName("label_3")
        self.verticalLayout_2.addWidget(self.label_3)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setContentsMargins(-1, -1, -1, 0)
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.label_4 = QtWidgets.QLabel(self.layoutWidget1)
        self.label_4.setAlignment(QtCore.Qt.AlignCenter)
        self.label_4.setObjectName("label_4")
        self.horizontalLayout_2.addWidget(self.label_4)
        self.label_5 = QtWidgets.QLabel(self.layoutWidget1)
        self.label_5.setAlignment(QtCore.Qt.AlignCenter)
        self.label_5.setObjectName("label_5")
        self.horizontalLayout_2.addWidget(self.label_5)
        self.label_6 = QtWidgets.QLabel(self.layoutWidget1)
        self.label_6.setAlignment(QtCore.Qt.AlignCenter)
        self.label_6.setObjectName("label_6")
        self.horizontalLayout_2.addWidget(self.label_6)
        self.verticalLayout_2.addLayout(self.horizontalLayout_2)
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.lineEditStart = QtWidgets.QLineEdit(self.layoutWidget1)
        self.lineEditStart.setObjectName("lineEditStart")
        self.horizontalLayout.addWidget(self.lineEditStart)
        self.lineEditEnd = QtWidgets.QLineEdit(self.layoutWidget1)
        self.lineEditEnd.setObjectName("lineEditEnd")
        self.horizontalLayout.addWidget(self.lineEditEnd)
        self.lineEditStep = QtWidgets.QLineEdit(self.layoutWidget1)
        self.lineEditStep.setObjectName("lineEditStep")
        self.horizontalLayout.addWidget(self.lineEditStep)
        self.verticalLayout_2.addLayout(self.horizontalLayout)
        self.pushButtonChangeTable = QtWidgets.QPushButton(self.layoutWidget1)
        self.pushButtonChangeTable.setObjectName("pushButtonChangeTable")
        self.verticalLayout_2.addWidget(self.pushButtonChangeTable)
        self.pushButtonShowTable = QtWidgets.QPushButton(self.layoutWidget1)
        self.pushButtonShowTable.setObjectName("pushButtonShowTable")
        self.verticalLayout_2.addWidget(self.pushButtonShowTable)
        self.textEdit = QtWidgets.QTextEdit(self.layoutWidget1)
        self.textEdit.setReadOnly(True)
        self.textEdit.setObjectName("textEdit")
        self.verticalLayout_2.addWidget(self.textEdit)
        self.layoutWidget2 = QtWidgets.QWidget(self.centralwidget)
        self.layoutWidget2.setGeometry(QtCore.QRect(300, 110, 264, 226))
        self.layoutWidget2.setObjectName("layoutWidget2")
        self.verticalLayout_4 = QtWidgets.QVBoxLayout(self.layoutWidget2)
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_4.setObjectName("verticalLayout_4")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout()
        self.verticalLayout_3.setSizeConstraint(QtWidgets.QLayout.SetNoConstraint)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.label_2 = QtWidgets.QLabel(self.layoutWidget2)
        self.label_2.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.label_2.setAlignment(QtCore.Qt.AlignCenter)
        self.label_2.setObjectName("label_2")
        self.verticalLayout_3.addWidget(self.label_2)
        self.formLayout_4 = QtWidgets.QFormLayout()
        self.formLayout_4.setLabelAlignment(QtCore.Qt.AlignCenter)
        self.formLayout_4.setObjectName("formLayout_4")
        self.label_8 = QtWidgets.QLabel(self.layoutWidget2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_8.sizePolicy().hasHeightForWidth())
        self.label_8.setSizePolicy(sizePolicy)
        self.label_8.setMaximumSize(QtCore.QSize(125, 25))
        self.label_8.setObjectName("label_8")
        self.formLayout_4.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.label_8)
        self.lineEditN = QtWidgets.QLineEdit(self.layoutWidget2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lineEditN.sizePolicy().hasHeightForWidth())
        self.lineEditN.setSizePolicy(sizePolicy)
        self.lineEditN.setMaximumSize(QtCore.QSize(125, 20))
        self.lineEditN.setObjectName("lineEditN")
        self.formLayout_4.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.lineEditN)
        self.verticalLayout_3.addLayout(self.formLayout_4)
        self.formLayout_3 = QtWidgets.QFormLayout()
        self.formLayout_3.setSizeConstraint(QtWidgets.QLayout.SetFixedSize)
        self.formLayout_3.setFieldGrowthPolicy(QtWidgets.QFormLayout.FieldsStayAtSizeHint)
        self.formLayout_3.setRowWrapPolicy(QtWidgets.QFormLayout.DontWrapRows)
        self.formLayout_3.setLabelAlignment(QtCore.Qt.AlignCenter)
        self.formLayout_3.setFormAlignment(QtCore.Qt.AlignCenter)
        self.formLayout_3.setObjectName("formLayout_3")
        self.label_9 = QtWidgets.QLabel(self.layoutWidget2)
        self.label_9.setEnabled(True)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_9.sizePolicy().hasHeightForWidth())
        self.label_9.setSizePolicy(sizePolicy)
        self.label_9.setMaximumSize(QtCore.QSize(125, 20))
        self.label_9.setTextFormat(QtCore.Qt.PlainText)
        self.label_9.setAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.label_9.setObjectName("label_9")
        self.formLayout_3.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.label_9)
        self.lineEditX = QtWidgets.QLineEdit(self.layoutWidget2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.lineEditX.sizePolicy().hasHeightForWidth())
        self.lineEditX.setSizePolicy(sizePolicy)
        self.lineEditX.setMaximumSize(QtCore.QSize(125, 25))
        self.lineEditX.setObjectName("lineEditX")
        self.formLayout_3.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.lineEditX)
        self.verticalLayout_3.addLayout(self.formLayout_3)
        self.radioButtonNewton = QtWidgets.QRadioButton(self.layoutWidget2)
        self.radioButtonNewton.setAcceptDrops(True)
        self.radioButtonNewton.setChecked(True)
        self.radioButtonNewton.setObjectName("radioButtonNewton")
        self.verticalLayout_3.addWidget(self.radioButtonNewton)
        self.radioButtonSpline = QtWidgets.QRadioButton(self.layoutWidget2)
        self.radioButtonSpline.setChecked(False)
        self.radioButtonSpline.setObjectName("radioButtonSpline")
        self.verticalLayout_3.addWidget(self.radioButtonSpline)
        self.pushButtonFindResult = QtWidgets.QPushButton(self.layoutWidget2)
        self.pushButtonFindResult.setObjectName("pushButtonFindResult")
        self.verticalLayout_3.addWidget(self.pushButtonFindResult)
        self.formLayout_2 = QtWidgets.QFormLayout()
        self.formLayout_2.setSizeConstraint(QtWidgets.QLayout.SetFixedSize)
        self.formLayout_2.setObjectName("formLayout_2")
        self.textEditResult = QtWidgets.QTextEdit(self.layoutWidget2)
        self.textEditResult.setEnabled(True)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.textEditResult.sizePolicy().hasHeightForWidth())
        self.textEditResult.setSizePolicy(sizePolicy)
        self.textEditResult.setMaximumSize(QtCore.QSize(125, 20))
        self.textEditResult.setReadOnly(True)
        self.textEditResult.setObjectName("textEditResult")
        self.formLayout_2.setWidget(0, QtWidgets.QFormLayout.FieldRole, self.textEditResult)
        self.label_10 = QtWidgets.QLabel(self.layoutWidget2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_10.sizePolicy().hasHeightForWidth())
        self.label_10.setSizePolicy(sizePolicy)
        self.label_10.setMaximumSize(QtCore.QSize(400, 25))
        self.label_10.setAlignment(QtCore.Qt.AlignCenter)
        self.label_10.setObjectName("label_10")
        self.formLayout_2.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.label_10)
        self.label_7 = QtWidgets.QLabel(self.layoutWidget2)
        self.label_7.setObjectName("label_7")
        self.formLayout_2.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.label_7)
        self.textEditRightResult = QtWidgets.QTextEdit(self.layoutWidget2)
        self.textEditRightResult.setEnabled(True)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.textEditRightResult.sizePolicy().hasHeightForWidth())
        self.textEditRightResult.setSizePolicy(sizePolicy)
        self.textEditRightResult.setMaximumSize(QtCore.QSize(125, 20))
        self.textEditRightResult.setReadOnly(True)
        self.textEditRightResult.setObjectName("textEditRightResult")
        self.formLayout_2.setWidget(1, QtWidgets.QFormLayout.FieldRole, self.textEditRightResult)
        self.verticalLayout_3.addLayout(self.formLayout_2)
        self.verticalLayout_4.addLayout(self.verticalLayout_3)
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.radioButtonNewton.toggled.connect(self.radiobutton_newton_is_clicked)
        self.radioButtonSpline.toggled.connect(self.radiobutton_spline_is_clicked)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.label.setText(_translate("MainWindow", "Аппроксимация функций"))
        self.label_3.setText(_translate("MainWindow", "Работа с таблицей"))
        self.label_4.setText(_translate("MainWindow", "От"))
        self.label_5.setText(_translate("MainWindow", "До"))
        self.label_6.setText(_translate("MainWindow", "Шаг"))
        self.pushButtonChangeTable.setText(_translate("MainWindow", "Изменить текущую \n"
"таблицу"))
        self.pushButtonShowTable.setText(_translate("MainWindow", "Показать текущую \n"
"таблицу"))
        self.label_2.setText(_translate("MainWindow", "Поиск значения"))
        self.label_8.setText(_translate("MainWindow", "Введите n >= 0: "))
        self.label_9.setText(_translate("MainWindow", "Введите x:          "))
        self.radioButtonNewton.setText(_translate("MainWindow", "Полином Ньютона"))
        self.radioButtonSpline.setText(_translate("MainWindow", "Сплайн"))
        self.pushButtonFindResult.setText(_translate("MainWindow", "Найти значения"))
        self.label_10.setText(_translate("MainWindow", "Результат:          "))
        self.label_7.setText(_translate("MainWindow", "Точный результат"))


    def radiobutton_newton_is_clicked(self, enabled):
        if enabled:
            self.lineEditN.setReadOnly(False)

    def radiobutton_spline_is_clicked(self, enabled):
        if enabled:
            self.lineEditN.setReadOnly(True)

