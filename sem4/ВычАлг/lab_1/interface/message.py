from PyQt5 import QtWidgets


class errorMessage(QtWidgets.QWidget):
    def __init__(self, text: str):
        super().__init__()
        self.title = 'Message'
        self.left = 10
        self.top = 10
        self.width = 320
        self.height = 200
        self.initUI(text)

    def initUI(self, text: str):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        QtWidgets.QMessageBox.critical(self, 'Critical error', text)

        self.show()


def showError(text: str):
    errorMessage(text)