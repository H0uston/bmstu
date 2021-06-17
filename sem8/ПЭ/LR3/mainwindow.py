from PyQt5 import uic
from PyQt5.QtWidgets import QMainWindow, QHeaderView
from matplotlib import pyplot
from PartialPlanTableWidget import *
from FullPlanTableWidget import *
from experiment_math import *
from model import *
import numpy as np
import math

def print_y(arrayOfB, string):
    xx = ['x1', 'x2', 'x3', 'x4', 'x5', 'x6']
    accuracy = 4
    iterator = 7
    for z in range(0, 5):
        for e in range(z + 1, 6):
            #res[i][7 + iterator] = res[i][z] * res[i][e] 
            string += " + " + str(round(arrayOfB[iterator], accuracy)) + xx[z] + xx[e]
            iterator += 1
            #if i == 1:
            #print(" " + str(z) + " : " + str(e))
    
    for z in range(0, 6):
        for e in range(z + 1, 6):
            for y in range(e + 1, 6):
                #res[i][7 + iterator] = res[i][z] * res[i][e] * res[i][y]
                string += " + " + str(round(arrayOfB[iterator], accuracy)) + xx[z] + xx[e] + xx[y]
                iterator += 1
                #if i == 1:
                    #print(" " + str(z) + " : " + str(e) + " : " + str(y))                    
        
    for z in range(0, 6):
        for e in range(z + 1, 6):
            for y in range(e + 1 , 6):
                for n in range(y + 1, 6):
                   #res[i][7 + iterator] = res[i][z] * res[i][e] * res[i][y] * res[i][n]
                    string += " + " + str(round(arrayOfB[iterator], accuracy)) + xx[z] + xx[e] + xx[y] + xx[n]
                    iterator += 1
                    #if i == 1:
                        #print(" " + str(z) + " : " + str(e) + " : " + str(y) + " : " + str(n))  
    
    for z in range(0, 6):
        for e in range(z + 1, 6):
            for y in range(e + 1, 6):
                for n in range(y + 1, 6):
                    for a in range(n + 1, 6):
                        #res[i][7 + iterator] = res[i][z] * res[i][e] * res[i][y] * res[i][n] * res[i][a]
                        string += " + " + str(round(arrayOfB[iterator], accuracy)) + xx[z] + xx[e] + xx[y] + xx[a]
                        iterator += 1
                       # if i == 1:
                            #print(" " + str(z) + " : " + str(e) + " : " + str(y) + " : " + str(n) + " : " + str(a)) 
                        
    z = 0
    e = 1
    y = 2
    n = 3
    a = 4
    l = 5
    string += " + " + str(round(arrayOfB[iterator], accuracy)) + xx[z] + xx[e] + xx[y] + xx[n] + xx[a] + xx[l]
    return string
    #res[i][7 + iterator] = res[i][z] * res[i][e] * res[i][y] * res[i][n] * res[i][a] * res[i][l]
    iterator += 1
    #if i == 1:
        #print(" " + str(z) + " : " + str(e) + " : " + str(y) + " : " + str(n) + " : " + str(a) + " : " + str(l)) 


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        uic.loadUi('mainwindow.ui', self)
        self.show()
        self.almost_zero = 1e-10
        #self.table_custom_full.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)
        #self.table_custom_partial.verticalHeader().setSectionResizeMode(QHeaderView.Stretch)

        self.full_plan = matrix_full_plan()
        self.partial_plan = matrix_partial_plan()
        self.custom_plan = [list(), list()]
        self.tab = FullPlanTableWidget()
        self.tab2 = PartialPlanTableWidget()

        self.btn_do_plan.clicked.connect(self.do_plan)
        self.btn_set1.clicked.connect(self.set_full)
        self.btn_set2.clicked.connect(self.set_partial)
        # self.btn_full.clicked.connect(self.show_table_full)
        # self.btn_partial.clicked.connect(self.show_table_partial)
        # self.btn_chart.clicked.connect(self.show_chart)

    def get_factor(self, entry):
        try:
            res = float(entry.text())
        except ValueError:
            entry.setStyleSheet("background:#f88;")
            raise ValueError()

        entry.setStyleSheet("background:#fff;")

        if abs(res) < self.almost_zero:
            res = self.almost_zero

        return res

    @staticmethod
    def get_custom_factor(entry):
        try:
            res = float(entry.text())
            if not -1 <= res <= 1:
                raise ValueError()
            if res.is_integer():
                res = int(res)
        except ValueError:
            entry.setStyleSheet("background:#f88;")
            raise ValueError()

        entry.setStyleSheet("background:#fff;")
        return res

    def do_plan(self):
        self.full_plan = matrix_full_plan()
        self.partial_plan = matrix_partial_plan()
        total_apps = 10000
        try:
            gen1_int_min = self.get_factor(self.entry_gen1_int_min)
            gen1_int_max = self.get_factor(self.entry_gen1_int_max)
            gen2_int_min = self.get_factor(self.entry_gen2_int_min)
            gen2_int_max = self.get_factor(self.entry_gen2_int_max)
            proc_int_min = self.get_factor(self.entry_proc_int_min)
            proc_int_max = self.get_factor(self.entry_proc_int_max)
            proc_dev_min = self.get_factor(self.entry_proc_dev_min)
            proc_dev_max = self.get_factor(self.entry_proc_dev_max)

            proc_int_min_2 = self.get_factor(self.entry_proc_int_min_2)
            proc_int_max_2 = self.get_factor(self.entry_proc_int_max_2)
            proc_dev_min_2 = self.get_factor(self.entry_proc_dev_min_2)
            proc_dev_max_2 = self.get_factor(self.entry_proc_dev_max_2)

        except ValueError:
            pass
        else:
            y = list()
            # for each experiment
            for exp in self.full_plan:
                gen_int1 = scale_factor(exp[1], gen1_int_min, gen1_int_max)
                gen_int2 = scale_factor(exp[2], gen2_int_min, gen2_int_max)
                proc_int = scale_factor(exp[3], proc_int_min, proc_int_max)
                proc_dev = scale_factor(exp[4], proc_dev_min, proc_dev_max)
                proc_int_2 = scale_factor(exp[5], proc_int_min_2, proc_int_max_2)
                proc_dev_2 = scale_factor(exp[6], proc_dev_min_2, proc_dev_max_2)
                proc_int = (proc_int + proc_int_2) / 2
                proc_dev = (proc_dev + proc_dev_2) / 2

                gens = [Generator(uniform_by_intensity, (gen_int1,)), Generator(uniform_by_intensity, (gen_int2,))]
                proc = Generator(rayleigh_by_intensity, (proc_int, proc_dev))
                model = EventModel(gens, proc, total_apps)

                y.append(model.proceed() / total_apps)

            for exp in self.custom_plan:
                if len(exp) > 0:
                    gen_int1 = scale_factor(exp[1], gen1_int_min, gen1_int_max)
                    gen_int2 = scale_factor(exp[2], gen2_int_min, gen2_int_max)
                    proc_int = scale_factor(exp[3], proc_int_min, proc_int_max)
                    proc_dev = scale_factor(exp[4], proc_dev_min, proc_dev_max)
                    proc_int_2 = scale_factor(exp[5], proc_int_min_2, proc_int_max_2)
                    proc_dev_2 = scale_factor(exp[6], proc_dev_min_2, proc_dev_max_2)
                    proc_int = (proc_int + proc_int_2) / 2
                    proc_dev = (proc_dev + proc_dev_2) / 2
                    gens = [Generator(uniform_by_intensity, (gen_int1,)), Generator(uniform_by_intensity, (gen_int2,))]
                    proc = Generator(rayleigh_by_intensity, (proc_int, proc_dev))
                    model = EventModel(gens, proc, total_apps)

                    y.append(round(model.proceed() / total_apps, 3))

                else:
                    y.append(None)

            bfull = expand_full_plan(self.full_plan, self.custom_plan[:1], y)
            bpart = expand_partial_plan(self.partial_plan, self.custom_plan[1:], y)

            self.set_equasions(bfull, bpart)
        self.show_table_full()
        self.show_table_partial()

    def set_equasions(self, bfull, bpart, accuracy=3):
        yl = str(round(bfull[0], accuracy)) + " + " + str(round(bfull[1], accuracy)) + "x1 + " + str(
            round(bfull[4], accuracy)) + "x2 + " + str(round(bfull[2], accuracy)) + "x3 + " + str(
            round(bfull[6], accuracy)) + "x4 + " + str(round(bfull[3], accuracy)) + "x5 + " + str(
                round(bfull[5], accuracy)) + "x6"
        yl = yl.replace("+ -", " - ")
        print("full yl: \n" +  yl)
        print("\n================================================\n")
        ynl = print_y(bfull, yl)
        ynl = ynl.replace(" + -", " - ")
        print("full ynl:\n" + ynl)
        ynl = ynl.replace("+ \n-", "-\n")
        # self.label_yfl.setText(yl)
        # self.label_yfnl.setText(ynl)
        print("\n================================================\n")
        yl = str(round(bpart[0], accuracy)) + " + " + str(round(bpart[1], accuracy)) + "x1 + " + str(
            round(bpart[4], accuracy)) + "x2 + " + str(round(bpart[2], accuracy)) + "x3 + " + str(
            round(bpart[6], accuracy)) + "x4 + " + str(round(bpart[3], accuracy)) + "x5 + " + str(round(bpart[5], accuracy)) + "x6"
        yl = yl.replace("+ -", " - ")
        print("partial yl:\n" + yl)
        ynl = print_y(bfull, yl)
        ynl = ynl.replace(" + -", " - ")
        print("partial ynl:\n" + ynl)
        #self.label_ypl.setText(yl)
        #self.label_ypnl.setText(ynl)

    def set_full(self):
        try:
            x1 = self.get_custom_factor(self.entry_x1_1)
            x2 = self.get_custom_factor(self.entry_x2_1)
            x3 = self.get_custom_factor(self.entry_x3_1)
            x4 = self.get_custom_factor(self.entry_x4_1)
            x5 = self.get_custom_factor(self.entry_x5_1)
            x6 = self.get_custom_factor(self.entry_x6_1)
        except ValueError:
            pass
        else:
            self.custom_plan[0] = [1, x1, x2, x3, x4, x5, x6, x1 * x2, x1 * x3, x1 * x4, x1 * x5, x1 * x6,
                                    x2 * x3, x2 * x4, x2 * x5, x2 * x6,
                                    x3 * x4, x3 * x5, x3 * x6,
                                    x4 * x5, x4 * x6,
                                    x5 * x6,
                                    x1 * x2 * x3, x1 * x2 * x4, x1 * x2 * x5, x1 * x2 * x6,
                                    x1 * x3 * x4, x1 * x3 * x5, x1 * x3 * x6,
                                    x1 * x4 * x5, x1 * x4 * x6,
                                    x1 * x5 * x6,
                                    x2 * x3 * x4, x2 * x3 * x5, x2 * x3 * x6,
                                    x2 * x4 * x5, x2 * x4 * x6,
                                    x2 * x5 * x6,
                                    x3 * x4 * x5, x3 * x4 * x6, x3 * x5 * x6,
                                    x4 * x5 * x6,
                                    x1 * x2 * x3 * x4, x1 * x2 * x3 * x5, x1 * x2 * x3 * x6,
                                    x1 * x2 * x4 * x5, x1 * x2 * x4 * x6,
                                    x1 * x2 * x5 * x6,
                                    x1 * x3 * x4 * x5, x1 * x3 * x4 * x6, x1 * x3 * x5 * x6,
                                    x1 * x4 * x5 * x6,
                                    x2 * x3 * x4 * x5, x2 * x3 * x4 * x6, x2 * x3 * x5 * x6,
                                    x2 * x4 * x5 * x6,
                                    x3 * x4 * x5 * x6, 
                                    x1 * x2 * x3 * x4 * x5, x1 * x2 * x3 * x4 * x6, x1 * x2 * x3 * x5 * x6, x1 * x2 * x4 * x5 * x6, x1 * x3 * x4 * x5 * x6,
                                    x2 * x3 * x4 * x5 * x6,
                                    x1 * x2 * x3 * x4 * x5 * x6]
            #for i in range(len(self.custom_plan[0])):
                #self.table_full.setItem(len(self.full_plan) + j + 1, i + 1, QTableWidgetItem(str(round(self.custom_plan[0][i], 3))))
                #self.table_custom_full.setItem(1, i + 1, QTableWidgetItem(str(self.custom_plan[0][i])))

    def set_partial(self):
        try:
            x1 = self.get_custom_factor(self.entry_x1_2)
            x2 = self.get_custom_factor(self.entry_x2_2)
            x3 = self.get_custom_factor(self.entry_x3_2)
            x4 = self.get_custom_factor(self.entry_x4_2)
            x5 = self.get_custom_factor(self.entry_x5_2)
            x6 = self.get_custom_factor(self.entry_x6_2)
        except ValueError:
            pass
        else:
            self.custom_plan[1] = [1, x1, x2, x3, x4, x5, x6, x1 * x2, x1 * x3, x1 * x4, x1 * x5, x1 * x6,
                                    x2 * x3, x2 * x4, x2 * x5, x2 * x6,
                                    x3 * x4, x3 * x5, x3 * x6,
                                    x4 * x5, x4 * x6,
                                    x5 * x6,
                                    x1 * x2 * x3, x1 * x2 * x4, x1 * x2 * x5, x1 * x2 * x6,
                                    x1 * x3 * x4, x1 * x3 * x5, x1 * x3 * x6,
                                    x1 * x4 * x5, x1 * x4 * x6,
                                    x1 * x5 * x6]
            #for i in range(len(self.custom_plan[1])):
                #self.table_custom_partial.setItem(1, i + 1, QTableWidgetItem(str(self.custom_plan[1][i])))

    @staticmethod
    def show_chart():
        max_int = 1
        total_apps = 300
        proc = Processor(1, 1)

        proc_dev = 100000
        proc = Processor(1/max_int, 1/proc_dev)
        Xdata = list()
        Ydata = list()

        for intensity in np.arange(1e-2, 1, 1e-1):
            t = 0
            for j in range(10):
                gen = Generator(uniform_by_intensity, (intensity,))
                model = EventModel([gen], proc, total_apps)
                t += (EventModel.proceed() / total_apps)
            Xdata.append(intensity / max_int)
            Ydata.append(t/100)

        pyplot.title('Average awaiting time')
        pyplot.grid(True)
        pyplot.plot(Xdata, Ydata)
        pyplot.xlabel("Strain (p)")
        pyplot.ylabel("Average time")
        pyplot.show()

    def show_table_full(self):
        # print(self.full_plan[0])
        for j in range(len(self.full_plan)):
            for i in range(len(self.full_plan[j])):
                self.table_full.setItem(j, i + 1, QTableWidgetItem(str(round(self.full_plan[j][i], 3))))
            for i in range(len(self.custom_plan[0])):
                self.table_full.setItem(len(self.full_plan) + j, i + 1, QTableWidgetItem(str(round(self.custom_plan[0][i], 3))))

    def show_table_partial(self):
        #print(len(self.custom_plan[1]))
        #print(len(self.partial_plan))
        #print(self.custom_plan)
        for j in range(len(self.partial_plan)):
            for i in range(len(self.partial_plan[j])):
                self.table_partial.setItem(j, i + 1, QTableWidgetItem(str(round(self.partial_plan[j][i], 3))))
            for i in range(len(self.custom_plan[1])):
                self.table_partial.setItem(len(self.partial_plan) + j, i + 1, QTableWidgetItem(str(round(self.custom_plan[1][i], 3))))