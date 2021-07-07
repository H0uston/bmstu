import tkinter as tk
import config
import function
import copy
import math
from tkinter import messagebox


class mainWindow(tk.Frame):
    def __init__(self, parent):
        tk.Frame.__init__(self, parent, background=config.windowBackgroundColour)
        self.parent = parent
        self.initUI()

    def initUI(self):
        self.parent.title(config.windowTitle)
        self.pack(fill=tk.BOTH, expand=1)

        # Settings:
        canvas = tk.Canvas(self, width=config.canvasWidth,
                           height=config.canvasHeight,
                           background="white",
                           borderwidth=0)
        canvas.place(x=config.canvasX,
                     y=config.canvasY)
        self.canvas = canvas
        firstSet = tk.Text(self,
                           width=config.firstSetWidth,
                           height=config.firstSetHeight,
                           borderwidth=0)
        firstSet.place(x=config.firstSetX,
                       y=config.firstSetY)
        self.firstEntry = firstSet
        secondSet = tk.Text(self,
                            width=config.secondSetWidth,
                            height=config.secondSetHeight,
                            borderwidth=0)
        secondSet.place(x=config.secondSetX,
                        y=config.secondSetY)
        self.secondEntry = secondSet
        buttonRun = tk.Button(self,
                              text=config.runButtonText,
                              font=config.runButtonFont,
                              width=config.runButtonWidth,
                              height=config.runButtonHeight,
                              borderwidth=0,
                              command=self.run)
        buttonRun.place(x=config.runButtonX,
                        y=config.runButtonY)

        buttonClear = tk.Button(self,
                                text=config.clearButtonText,
                                font=config.clearButtonFont,
                                width=config.clearButtonWidth,
                                height=config.clearButtonHeight,
                                borderwidth=0,
                                command=self.clear)
        buttonClear.place(x=config.clearButtonX,
                          y=config.clearButtonY)

        firstSetLabel = tk.Label(self,
                                 text=config.firstSetLabelText,
                                 font=config.firstSetLabelFont,
                                 background=config.setLabelBackground)
        firstSetLabel.place(x=config.firstSetLabelX,
                            y=config.firstSetLabelY)
        secondSetLabel = tk.Label(self,
                                  text=config.secondSetLabelText,
                                  font=config.secondSetLabelFont,
                                  background=config.setLabelBackground)
        secondSetLabel.place(x=config.secondSetLabelX,
                             y=config.secondSetLabelY)
        canvas.create_line(config.xAxisXA, config.yAxisXA,
                           config.xAxisXB, config.yAxisXB, arrow=tk.LAST)
        canvas.create_text(config.xTextAxisX, config.yTextAxisX, text=config.textAxisX)
        canvas.create_line(config.xAxisYA, config.yAxisYA,
                           config.xAxisYB, config.yAxisYB, arrow=tk.LAST)
        canvas.create_text(config.xTextAxisY, config.yTextAxisY, text=config.textAxisY)
        mainMenu = tk.Menu(self)
        self.parent.config(menu=mainMenu)
        infoMenu = tk.Menu(mainMenu, tearoff=0)
        infoMenu.add_command(label="Разработчик", command=self.developer)
        infoMenu.add_command(label="Информация", command=self.info)
        mainMenu.add_cascade(label="Help", menu=infoMenu)

    # Two text widgets:
    firstEntry = None
    secondEntry = None
    # Label widget
    answer = None
    # Canvas
    canvas = None

    def run(self):
        if self.answer != None:
            self.answer.place_forget()
        self.canvas.delete('all')
        self.canvas.create_line(config.xAxisXA, config.yAxisXA,
                                config.xAxisXB, config.yAxisXB, arrow=tk.LAST)
        self.canvas.create_text(config.xTextAxisX, config.yTextAxisX, text=config.textAxisX)
        self.canvas.create_line(config.xAxisYA, config.yAxisYA,
                                config.xAxisYB, config.yAxisYB, arrow=tk.LAST)
        self.canvas.create_text(config.xTextAxisY, config.yTextAxisY, text=config.textAxisY)

        firstSetText = self.firstEntry.get(0.0, tk.END)
        secondSetText = self.secondEntry.get(0.0, tk.END)
        coordinations, angle, error = function.mainFunc(firstSetText, secondSetText)
        oldCoordinations = copy.deepcopy(coordinations)
        if coordinations == None or angle == None or len(coordinations) != 2 or error == 1:
            messagebox.showerror("Error!", "Неверный ввод!\nОзнакомьтесь с меню info")
            return None
        elif error == 2:
            messagebox.showerror("Error!", "Неверный ввод!\nВсе точки одного из множеств лежат на одной прямой")
            return None

        line = [0, 0]
        line[0] = function.calcOrthocenter(coordinations[0])
        line[1] = function.calcOrthocenter(coordinations[1])
        coordinations.append(line)


        coordinations = function.scaling(coordinations)
        line = coordinations.pop()

        self.drawTriangle(coordinations[0])
        self.drawTriangle(coordinations[1])
        self.canvas.create_line(line[0][0], line[0][1], line[1][0], line[1][1], fill="green")
        for i in range(2):
            self.drawExtra(coordinations[i], line[i])
        for i in range(len(coordinations)):
            for j in range(len(coordinations[i])):
                self.canvas.create_text(coordinations[i][j][0], coordinations[i][j][1] - config.yIndentSign,
                                        text=str(oldCoordinations[i][j]), font=config.fontSign,
                                        fill=config.fillSign)
        text = config.textAnswer.format(str(round(math.degrees(angle), 2)),
                str(oldCoordinations[0][0]), str(oldCoordinations[0][1]), str(oldCoordinations[0][2]),
                str(oldCoordinations[1][0]), str(oldCoordinations[1][1]), str(oldCoordinations[1][2]))
        answer = tk.Label(self,
                          borderwidth=0,
                          background=config.answerBackgroundColour,
                          text=text)
        answer.place(x=config.answerX,
                     y=config.answerY)
        self.answer = answer


    def clear(self):
        self.firstEntry.delete('1.0', tk.END)
        self.secondEntry.delete('1.0', tk.END)
        self.canvas.delete('all')
        self.answer.place_forget()
        self.canvas.create_line(config.xAxisXA, config.yAxisXA,
                           config.xAxisXB, config.yAxisXB, arrow=tk.LAST)
        self.canvas.create_text(config.xTextAxisX, config.yTextAxisX, text=config.textAxisX)
        self.canvas.create_line(config.xAxisYA, config.yAxisYA,
                           config.xAxisYB, config.yAxisYB, arrow=tk.LAST)
        self.canvas.create_text(config.xTextAxisY, config.yTextAxisY, text=config.textAxisY)

    def drawTriangle(self, points):
        self.canvas.create_line(points[0][0], points[0][1],
                                points[1][0], points[1][1])
        self.canvas.create_line(points[1][0], points[1][1],
                                points[2][0], points[2][1])
        self.canvas.create_line(points[2][0], points[2][1],
                                points[0][0], points[0][1])


    def developer(self):
        messagebox.showinfo("Info", config.developerInfo)

    def info(self):
        messagebox.showinfo("Info", config.helpInfo)

    def drawExtra(self, threePoints: list, line: list):
        first, second, third = threePoints
        self.canvas.create_line(first[0], first[1], line[0], line[1], fill="red")
        self.canvas.create_line(second[0], second[1], line[0], line[1], fill="red")
        points = function.extraSchame(threePoints)
        self.canvas.create_line(third[0], third[1], points[0][0], points[0][1], fill="blue")
        self.canvas.create_line(first[0], first[1], points[1][0], points[1][1], fill="blue")

def main() -> None:
    root = tk.Tk()
    root.geometry(str(config.windowWidth) + 'x' + str(config.windowHeight))
    root.resizable(width=False, height=False)
    app = mainWindow(root)
    root.mainloop()


if __name__ == "__main__":
    main()

