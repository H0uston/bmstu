#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_mainwindow.h>
#include "lift.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_1_floor_in_cabin_clicked();
    void on_button_2_floor_in_cabin_clicked();
    void on_button_3_floor_in_cabin_clicked();
    void on_button_4_floor_in_cabin_clicked();
    void on_button_5_floor_in_cabin_clicked();

    void on_button_on_1_floor_clicked();
    void on_button_on_2_floor_clicked();
    void on_button_on_3_floor_clicked();
    void on_button_on_4_floor_clicked();
    void on_button_on_5_floor_clicked();

private:
    Ui::MainWindow *ui;
    Lift lift;
};

#endif // MAINWINDOW_H
