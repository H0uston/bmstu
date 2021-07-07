#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QPalette>
#include "my_paintwidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_choose_color_pushButton_clicked();

    void on_draw_surface_pushButton_clicked();

    void on_clear_pushButton_clicked();

    void on_rotate_pushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    my_paintwidget *myscene;
    Function functionT;
    transform_params params;
    surface_data cur_data;
    void rotate(void);
    bool key_down_pressed;
    bool key_up_pressed;
    bool key_right_pressed;
    bool key_left_pressed;
    bool key_z_pressed;
};

#endif // MAINWINDOW_H
