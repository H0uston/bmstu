import sys
from PyQt5 import QtWidgets
import sources
from gui import window

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    w = window.Window()
    w.show()
    sys.exit(app.exec_())
