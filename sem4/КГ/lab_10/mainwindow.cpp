#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDoubleValidator>
#include <QKeyEvent>

void change_widget_color(QWidget *widg, QColor color)
{
    QPalette pal = widg->palette();
    pal.setColor(QPalette::Window, color);
    widg->setPalette(pal);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDoubleValidator *v = new QDoubleValidator(this);
    v->setLocale(QLocale::English);
    ui->x_start_lineEdit->setValidator(v);
    ui->x_end_lineEdit->setValidator(v);
    ui->delta_x_lineEdit->setValidator(v);
    ui->z_start_lineEdit->setValidator(v);
    ui->z_end_lineEdit->setValidator(v);
    ui->delta_z_lineEdit->setValidator(v);
    ui->rotate_ox_lineEdit->setValidator(v);
    ui->rotate_oy_lineEdit->setValidator(v);
    ui->rotate_oz_lineEdit->setValidator(v);
    ui->k_lineEdit->setValidator(v);


    ui->comboBox_surface->addItem("Выберете поверхность");
    ui->comboBox_surface->addItem(functionT.get_function_name(1));
    ui->comboBox_surface->addItem(functionT.get_function_name(2));
    ui->comboBox_surface->addItem(functionT.get_function_name(3));
    ui->comboBox_surface->addItem(functionT.get_function_name(4));
    ui->comboBox_surface->addItem(functionT.get_function_name(5));


    ui->color_widget->setAutoFillBackground(true);
    change_widget_color(ui->color_widget, QColor(Qt::white));

    myscene = new my_paintwidget(ui->draw_widget);
    myscene->setMinimumSize(X_MAX, Y_MAX);

    params.angle_x = 0;
    params.angle_y = 0;
    params.angle_z = 0;
    params.k = 30;

    key_down_pressed = false;
    key_up_pressed = false;
    key_right_pressed = false;
    key_left_pressed = false;
    key_z_pressed = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_choose_color_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Веберете цвет");
    if (color.isValid())
    {
        change_widget_color(ui->color_widget, color);
        myscene->set_draw_color(color);
    }
}

void MainWindow::on_draw_surface_pushButton_clicked()
{
    if (ui->comboBox_surface->currentIndex() == 0)
        QMessageBox::information(this, "Поверхность", "Выберете поверхность");
    else
    {
        cur_data.x_start = ui->x_start_lineEdit->text().toDouble();
        cur_data.x_end = ui->x_end_lineEdit->text().toDouble();
        cur_data.x_step = ui->delta_x_lineEdit->text().toDouble();
        cur_data.z_start = ui->z_start_lineEdit->text().toDouble();
        cur_data.z_end = ui->x_end_lineEdit->text().toDouble();
        cur_data.z_step = ui->delta_z_lineEdit->text().toDouble();
        cur_data.func = functionT.get_function(ui->comboBox_surface->currentIndex() - 1);
        myscene->draw_surface(cur_data, params);
        myscene->repaint();
    }
}

void MainWindow::on_clear_pushButton_clicked()
{
    myscene->clear();
    myscene->repaint();
    params.angle_x = 0;
    params.angle_y = 0;
    params.angle_z = 0;
    params.k = 30;
}

void correct_data(transform_params &p)
{
    if (p.angle_x > 360)
        p.angle_x -= 360;
    else if (p.angle_x < -360)
        p.angle_x += 360;
    if (p.angle_y > 360)
        p.angle_y -= 360;
    else if (p.angle_y < -360)
        p.angle_y += 360;
    if (p.angle_z > 360)
        p.angle_z -= 360;
    else if (p.angle_z < -360)
        p.angle_z += 360;
}

void MainWindow::on_rotate_pushButton_clicked()
{
    params.angle_x += ui->rotate_ox_lineEdit->text().toDouble();
    params.angle_y += ui->rotate_oy_lineEdit->text().toDouble();
    params.angle_z += ui->rotate_oz_lineEdit->text().toDouble();
    correct_data(params);
    myscene->draw_surface(cur_data, params);
    myscene->repaint();
}

void MainWindow::on_pushButton_clicked()
{
    double cur_k = ui->k_lineEdit->text().toDouble();
    if (params.k + cur_k != 0)
    {
        params.k += ui->k_lineEdit->text().toDouble();
        myscene->draw_surface(cur_data, params);
        myscene->repaint();
    }
    else
        QMessageBox::warning(this, "Вырождение в точку", "Дальнейшее масштабирование с заданным коэффициентом приведет к вырождению изображения в точку");

}

void MainWindow::rotate()
{
    if (key_down_pressed)
        params.angle_x -= ui->rotate_ox_lineEdit->text().toDouble();
    if (key_up_pressed)
        params.angle_x += ui->rotate_ox_lineEdit->text().toDouble();
    if (key_left_pressed)
        params.angle_y -= ui->rotate_oy_lineEdit->text().toDouble();
    if (key_right_pressed)
        params.angle_y += ui->rotate_oy_lineEdit->text().toDouble();
    if (key_z_pressed)
        params.angle_z += ui->rotate_oz_lineEdit->text().toDouble();
    correct_data(params);
    myscene->draw_surface(cur_data, params);
    myscene->repaint();
}
