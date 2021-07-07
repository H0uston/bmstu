import sys
from PyQt5 import QtCore, QtGui, QtWidgets
from gui.interfaceWindow import *
import sources.window


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    myapp = sources.window.MyWin()
    myapp.show()
    sys.exit(app.exec_())
