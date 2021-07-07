#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QRegExpValidator>
#include "paintwidget.h"

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
    void addPointEnabled();

    void on_changeBGColourButton_clicked();
    void on_changeSegmentColourButton_clicked();
    void on_changeCutterColourButton_clicked();
    void on_changeCutColourButton_clicked();

    void on_addPointButton_clicked();

    void on_clearButton_clicked();
    void on_cutButton_clicked();
    void on_clearCutterButton_clicked();

    void on_segmentRadioButton_clicked();
    void on_cutterRadioButton_clicked();

private:
    PaintWidget *paint_widget;
    Ui::MainWindow *ui;
    bool enable_add;
};

#endif // MAINWINDOW_H
