#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <string>
#include <sstream>
#include "io/parser.h"
#include "render_manager/render_manager.h"

#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startPushButton_clicked();
    void on_stopPushButton_clicked();
    void on_addTreePushButton_clicked();
    void on_addTreesPushButton_clicked();
    void on_quitAddTreesPushButton_clicked();
    void keyPressEvent(QKeyEvent *event);
    void MoveTrain();
    void mousePressEvent(QMouseEvent *event);


private:
    void end_of_movement();
    void loadModels();
    void move_and_render_train();
    Model_manager *mm;
    Ui::MainWindow *ui;
    Render_manager *render_manager;

    bool moving = false;
    QTimer* timerForTrain;
    int timer = 1;

    CameraAttributes old_attr;
    bool add_tree_mode = false;
    bool moving_on = false;
    bool stopped = false;


};

#endif // MAINWINDOW_H
