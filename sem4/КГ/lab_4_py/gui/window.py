from PyQt5.QtGui import QPen, QColor, QImage, QPixmap, QPalette
from PyQt5.QtCore import Qt
import sources.config as config
from gui.mainWindow_ui import *
import sources.checker as checker
import gui.message as message
import sources.function as function


class Window(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        # uic.loadUi("gui/mainwindow.ui", self)
        self.scene = QtWidgets.QGraphicsScene(0, 0, config.CANVAS_WIDTH - 15,
                                              config.CANVAS_HEIGHT - 15)
        self.image = QImage(515, 515,  # Why 515? idk, pixmap makes glitches on screen if > 515
                            QImage.Format_ARGB32_Premultiplied)
        self.ui.graphicsView.setScene(self.scene)

        self.pen = QPen()
        self.pen_colour = QColor(Qt.black)
        self.chosen_colour = QColor(Qt.black)

        self.palette = QPalette()
        self.palette.setColor(QPalette.Background, self.pen_colour)

        self.ui.cleanButton.clicked.connect(self.clean_all)
        self.ui.drawButton.clicked.connect(self.draw)
        self.ui.chooseButton.clicked.connect(self.choose_colour)
        self.ui.radioButtonColour.clicked.connect(self.change_colour)
        self.ui.radioButtonWhite.clicked.connect(self.change_colour)

    def clean_all(self):
        """
        Cleans scene AND image
        :return: Nothing
        """
        self.scene.clear()
        self.image.fill(Qt.color0)

    def check_circle(self) -> list or None:
        """
        Checks data of all "Circle" lineEdits
        :return: list [x, y, radius] if data are correct otherwise None
        """
        x_text = self.ui.lineEditCX.text()
        xc = float(x_text) if checker.check_float(x_text) else None
        y_text = self.ui.lineEditCY.text()
        yc = float(y_text) if checker.check_float(y_text) else None
        radius_text = self.ui.lineEditRad.text()
        radius = (float(radius_text) if checker.check_float(radius_text) and
                  float(radius_text) > 0 else None)
        if xc is None or yc is None or radius is None:
            return None
        else:
            return [xc, yc, radius]

    def check_ellipse(self) -> list or None:
        """
        Checks data of all "Ellipse" lineEdits
        :return: list [x, y, a, b] if data are correct otherwise None
        """
        x_text = self.ui.lineEditEX.text()
        xc = float(x_text) if checker.check_float(x_text) else None
        y_text = self.ui.lineEditEY.text()
        yc = float(y_text) if checker.check_float(y_text) else None
        a_text = self.ui.lineEditEA.text()
        a = float(a_text) if (checker.check_float(a_text) and
                              float(a_text) > 0) else None
        b_text = self.ui.lineEditEB.text()
        b = float(b_text) if (checker.check_float(b_text) and
                              float(b_text) > 0) else None

        if xc is None or yc is None or a is None or b is None:
            return None
        else:
            return [xc, yc, a, b]

    def check_concenter(self) -> list or None:
        """
        Checks data of all "Concenter" lineEdits
        :return: list [step, count] if data are correct otherwise None
        """
        step_text = self.ui.lineEditStep.text()
        step = float(step_text) if checker.check_float(step_text) else None
        count_text = self.ui.lineEditCount.text()
        count = int(count_text) if (checker.check_float(count_text)
                                    and int(count_text) > 0) else None

        if step is None or count is None:
            return None
        else:
            return [step, count]

    def draw(self) -> None:
        """
        Draws one or few ellipses or circles
        :return: None if data aren't correct
        """
        concenter = False
        if self.ui.checkConcenter.isChecked():
            concenter = True
            data_concenter = self.check_concenter()
            if data_concenter is None:
                message.show_error(config.USER_ERR3)
                return None

        if self.ui.tabWidget.currentIndex() == 0:  # means circle
            data_circle = self.check_circle()
            if data_circle is None:  # if data aren't correct
                message.show_error(config.USER_ERR1)
                return None

            current_algorithm = self.ui.comboBox.currentText()  # Get name of method
            if concenter:  # if checkbox of concenter is checked
                step, count = data_concenter
                for i in range(count):
                    function.draw_circle(self, data_circle, current_algorithm)
                    data_circle[2] += step
            else:
                function.draw_circle(self, data_circle, current_algorithm)

        elif self.ui.tabWidget.currentIndex() == 1:  # means ellipse
            data_ellipse = self.check_ellipse()
            if data_ellipse is None:
                message.show_error(config.USER_ERR2)
                return None

            current_algorithm = self.ui.comboBox.currentText()  # Get name of method
            if concenter:  # if checkbox of concenter is checked
                step, count = data_concenter

                # We must know bigger side of ellipse to prevent its deformation
                a_bigger = data_ellipse[2] > data_ellipse[3]

                for i in range(count):
                    function.draw_ellipse(self, data_ellipse, current_algorithm)
                    # Bigger side must expands on step
                    # Smaller only on part of it
                    if a_bigger:
                        data_ellipse[2] += step
                        data_ellipse[3] += data_ellipse[3] / data_ellipse[2] * step
                    else:
                        data_ellipse[3] += step
                        data_ellipse[2] += data_ellipse[2] / data_ellipse[3] * step
            else:
                function.draw_ellipse(self, data_ellipse, current_algorithm)

        else:
            message.show_error(config.PROG_ERR2)
            return None

    def choose_colour(self) -> None:
        """
        User chooses colour in QColorDialog. Colour of frame sets chosen colour.
        :return: Nothing
        """
        self.chosen_colour = QtWidgets.QColorDialog.getColor(Qt.white, self, "Выберите цвет")
        self.pen_colour = self.chosen_colour
        self.palette.setColor(QPalette.Background, self.chosen_colour)
        self.ui.frame.setPalette(self.palette)

    def paint(self) -> None:
        """
        Draws figures on scene
        :return: Nothing
        """
        pix = QPixmap(0, 0)
        pix.convertFromImage(self.image)
        self.scene.addPixmap(pix)

    def change_colour(self) -> None:
        """
        Changes colour of pen (using radio buttons)
        :return: Nothing
        """
        if self.ui.radioButtonWhite.isChecked():
            self.pen_colour = QColor(Qt.white)
        elif self.ui.radioButtonColour.isChecked():
            self.pen_colour = self.chosen_colour
        else:  # Impossible but better to control
            message.show_error(config.PROG_ERR3)
            return None
