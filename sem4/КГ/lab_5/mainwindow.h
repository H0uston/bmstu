#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <math.h>
#include <QVector>
#include <QPixmapCache>
#include <QLabel>
#include <QPainter>
#include <QMessageBox>
#include <QDialog>
#include <QColorDialog>
#include <QTime>
#include <iostream>

#include "edge.h"

#define OFFSET 10.0
#define EPS 0.0000001

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);
    bool canvas_was_not_pushed = true;
    bool first_click = true;
    double curr_x = -1;
    double curr_y = -1;
    double prev_x = -1;
    double prev_y = -1;

private slots:
    void on_borderColourPushButton_clicked();
    void on_fillColourPushButton_clicked();
    void on_bgColourPushButton_clicked();
    void on_clearPushButton_clicked();
    void on_addPointPushButton_clicked();
    void on_keyboardRadioButton_clicked();
    void on_mouseRadioButton_clicked();
    void on_closePushButton_clicked();
    void on_fillPushButton_clicked();

private:
    void change_background();
    Ui::MainWindow *ui;
    QPixmap *scene;
    QPainter *painter;
    QColor border_colour;
    QColor fill_colour;
    QColor bg_colour;
    QVector <edge_t> all_edges;
};

void sleepFeature(const int &time);

#endif // MAINWINDOW_H
