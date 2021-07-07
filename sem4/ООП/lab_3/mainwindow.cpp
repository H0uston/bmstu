#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lift.set_consol(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_1_floor_in_cabin_clicked()
{
    ui->textEdit->append("В кабине лифта нажата кнопка первого этажа.");
    lift.add_stop(1);
}

void MainWindow::on_button_2_floor_in_cabin_clicked()
{
    ui->textEdit->append("В кабине лифта нажата кнопка второго этажа.");
    lift.add_stop(2);
}

void MainWindow::on_button_3_floor_in_cabin_clicked()
{
    ui->textEdit->append("В кабине лифта нажата кнопка третьего этажа.");
    lift.add_stop(3);
}

void MainWindow::on_button_4_floor_in_cabin_clicked()
{
    ui->textEdit->append("В кабине лифта нажата кнопка четвертого этажа.");
    lift.add_stop(4);
}

void MainWindow::on_button_5_floor_in_cabin_clicked()
{
    ui->textEdit->append("В кабине лифта нажата кнопка пятого этажа.");
    lift.add_stop(5);
}

void MainWindow::on_button_on_1_floor_clicked()
{
    ui->textEdit->append("Лифт вызван на первом этаже.");
    lift.add_stop(1);
}

void MainWindow::on_button_on_2_floor_clicked()
{
    ui->textEdit->append("Лифт вызван на втором этаже.");
    lift.add_stop(2);
}

void MainWindow::on_button_on_3_floor_clicked()
{
    ui->textEdit->append("Лифт вызван на третьем этаже.");
    lift.add_stop(3);
}

void MainWindow::on_button_on_4_floor_clicked()
{
    ui->textEdit->append("Лифт вызван на четвёртом этаже.");
    lift.add_stop(4);
}

void MainWindow::on_button_on_5_floor_clicked()
{
    ui->textEdit->append("Лифт вызван на пятом этаже.");
    lift.add_stop(5);
}
