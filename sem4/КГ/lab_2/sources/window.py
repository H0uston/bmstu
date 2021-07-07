from PyQt5 import QtWidgets
from PyQt5.QtCore import Qt
from gui.interfaceWindow import *
import math
import sources.config as config
import sources.function as function
import copy
import gui.message as message


class MyWin(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        self.pen = QtGui.QPen(QtGui.QColor(0, 0, 0))  # Set colour of pen
        self.pen.setWidth(3)  # Set width of lines
        self.brush = QtGui.QBrush(Qt.BDiagPattern)  # Set kind of filling (diagonal hatching)

        self.red_pen = QtGui.QPen(QtGui.QColor(255, 0, 0))
        self.red_pen.setWidth(3)
        self.red_brush = QtGui.QBrush(QtGui.QColor(255, 0, 0))

        self.scene = QtWidgets.QGraphicsScene()
        self.default_image()  # draw default image
        self.scene.setSceneRect(0, 0, 545, 545)  # Make scene fixed
        self.draw_red_center()  # Draw red point in center of scene
        self.ui.graphicsView.setScene(self.scene)

        # Connect buttons
        self.ui.rotateButton.clicked.connect(self.rotate_image)
        self.ui.scaleButton.clicked.connect(self.scale_image)
        self.ui.moveButton.clicked.connect(self.move_image)
        self.ui.stepBackButton.clicked.connect(self.step_back)
        self.ui.stepForwardButton.clicked.connect(self.step_forward)
        self.ui.defaultImageButton.clicked.connect(self.default_image)

    pen = None
    red_pen = None
    brush = None
    red_brush = None
    scene = None
    past = []  # List of past points
    curr = []  # List of current points
    next = []  # List of next points

    # Draw red point in center of scene
    def draw_red_center(self):
        self.scene.addEllipse(config.CANVASSIZE / 2 - 2, config.CANVASSIZE / 2 - 2, 5, 5,
                              self.red_pen, self.red_brush)
        self.ui.graphicsView.setScene(self.scene)

    # Form QPolygon from points
    @staticmethod
    def make_polygon(points: list) -> object:
        polygon = QtGui.QPolygonF()
        for i in range(len(points)):
            polygon.append(QtCore.QPointF(points[i][0], points[i][1]))
        return polygon

    # Move the image on dx or dy
    def move_image(self):
        dx = self.ui.moveDxLineEdit.text()
        dy = self.ui.moveDyLineEdit.text()

        if function.check_float(dx) and function.check_float(dy):
            dx = float(dx)
            dy = float(dy)
        else:
            message.errorMessage("Неверные данные!")
            return None

        points = copy.deepcopy(self.curr)
        self.past.append(self.curr)
        self.curr = []
        for i in range(len(points)):
            points[i][0] += dx
            points[i][1] += dy
        self.curr = copy.deepcopy(points)
        self.draw_image()
        return points

    # rotate image on angle (in degrees) relative to the center (x, y)
    def rotate_image(self):
        x_center = self.ui.rotateXLineEdit.text()
        y_center = self.ui.rotateYLineEdit.text()
        angle = self.ui.rotateAngleLineEdit.text()

        # Checking of data
        if (function.check_float(x_center) and function.check_float(y_center)
                and function.check_float(angle)):
            x_center = float(x_center) + config.CANVASSIZE / 2
            y_center = float(y_center) + config.CANVASSIZE / 2
            angle = float(angle)  # Angle in degrees
            angle = math.radians(angle)  # Make angle in radians
        else:
            message.errorMessage("Неверные данные!")
            return None

        points = copy.deepcopy(self.curr)
        self.past.append(self.curr)
        self.curr = []
        for i in range(len(points)):
            x, y = points[i]
            points[i][0] = (x_center + (x - x_center) * math.cos(angle) +
                            (y - y_center) * math.sin(angle))

            points[i][1] = (y_center + (y - y_center) * math.cos(angle) -
                            (x - x_center) * math.sin(angle))
        self.curr = copy.deepcopy(points)
        self.draw_image()

    # Scale the image (kx, ky) relative to the center
    def scale_image(self):
        x_center = self.ui.scaleXLineEdit.text()
        y_center = self.ui.scaleYLineEdit.text()
        kx = self.ui.scaleKxLineEdit.text()
        ky = self.ui.scaleKyLineEdit.text()

        # Checking of data
        if (function.check_float(x_center) and function.check_float(y_center) and
                function.check_float(kx) and function.check_float(ky)):
            x_center = float(x_center) + config.CANVASSIZE / 2
            y_center = float(y_center) + config.CANVASSIZE / 2
            kx = float(kx)
            ky = float(ky)
        else:
            message.errorMessage("Неверные данные!")
            return None

        points = copy.deepcopy(self.curr)
        self.past.append(self.curr)
        self.curr = []
        for i in range(len(points)):
            x, y = points[i]
            points[i][0] = x * kx + x_center * (1 - kx)
            points[i][1] = y * ky + y_center * (1 - ky)
        self.curr = copy.deepcopy(points)
        self.draw_image()

    # Draw current image on the scene
    def draw_image(self):
        self.scene.clear()
        self.draw_red_center()
        polygon = self.make_polygon(self.curr)
        self.scene.addPolygon(polygon, self.pen, self.brush)
        self.ui.graphicsView.setScene(self.scene)

    # Draw past image
    def step_back(self):
        if len(self.past) == 0:
            message.errorMessage("Действие невозможно!")
            return None
        points = copy.deepcopy(self.curr)
        self.next.append(points)
        self.curr = self.past.pop()
        self.draw_image()

    # Draw next image
    def step_forward(self):
        if len(self.next) == 0:
            message.errorMessage("Действие невозможно!")
            return None
        points = copy.deepcopy(self.curr)
        self.past.append(points)
        self.curr = self.next.pop()
        self.draw_image()

    # Draw default image
    def default_image(self):
        self.past = []
        self.next = []
        points = function.form_default_points()
        self.curr = copy.deepcopy(points)
        self.draw_image()
