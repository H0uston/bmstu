#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <string.h>
#include <iostream>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QCloseEvent>

#include "config.h"
#include "shape.h"
#include "controller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    edge_t *edges = nullptr;
    point_t *points = nullptr;

private slots:
    void on_changed();
    void on_inputPushButton_clicked();
    void on_rotatePushButton_clicked();
    void on_movePushButton_clicked();
    void on_scalePushButton_clicked();
    void on_outputPushButton_clicked();
    void closeEvent(QCloseEvent *event);

private:
    int file_success = 0;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    parameters_t parameters;
    void show_error(int code_error);
};

#endif // MAINWINDOW_H
