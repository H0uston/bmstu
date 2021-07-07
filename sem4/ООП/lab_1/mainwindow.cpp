#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    this->setWindowTitle("Работа с каркасной моделью");

    QRegExp check_filename("[0-9a-z_]+\\.[a-z]+");
    QRegExpValidator *file_validator = new QRegExpValidator(check_filename, this);

    QRegExp check_double("[-+]?(\\d+(\\.\\d*)?|\\.\\d+)$");
    QRegExpValidator *double_validator = new QRegExpValidator(check_double, this);

    ui->inputLineEdit->setValidator(file_validator);
    ui->outputLineEdit->setValidator(file_validator);
    connect(ui->inputLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(ui->outputLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));

    ui->dxLineEdit->setValidator(double_validator);
    ui->dyLineEdit->setValidator(double_validator);
    ui->dzLineEdit->setValidator(double_validator);
    connect(ui->dxLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(ui->dyLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(ui->dzLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));

    ui->kxLineEdit->setValidator(double_validator);
    ui->kyLineEdit->setValidator(double_validator);
    ui->kzLineEdit->setValidator(double_validator);
    connect(ui->kxLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(ui->kyLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));
    connect(ui->kzLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));

    ui->angleLineEdit->setValidator(double_validator);
    connect(ui->angleLineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_changed()));

    ui->rotatePushButton->setEnabled(false);
    ui->movePushButton->setEnabled(false);
    ui->scalePushButton->setEnabled(false);
    ui->inputPushButton->setEnabled(false);
    ui->outputPushButton->setEnabled(false);

    scene->setSceneRect(X - X, Y - Y, X - 20, Y - 20);
    scene->addLine(X / 2, Y - Y, X / 2, Y);
    scene->addLine(X - X, Y / 2, X, Y / 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_changed()
{
    if (ui->inputLineEdit->hasAcceptableInput())
    {
        ui->inputPushButton->setEnabled(true);
    }
    else
    {
        ui->inputPushButton->setEnabled(false);
    }

    if (file_success == 1)
    {
        if (ui->dxLineEdit->hasAcceptableInput() &&
            ui->dyLineEdit->hasAcceptableInput() &&
            ui->dzLineEdit->hasAcceptableInput())
        {
            ui->movePushButton->setEnabled(true);
        }
        else
        {
            ui->movePushButton->setEnabled(false);
        }

        if (ui->kxLineEdit->hasAcceptableInput() &&
            ui->kyLineEdit->hasAcceptableInput() &&
            ui->kzLineEdit->hasAcceptableInput()) {
            ui->scalePushButton->setEnabled(true);
        }
        else
        {
            ui->scalePushButton->setEnabled(false);
        }

        if (ui->angleLineEdit->hasAcceptableInput())
        {
            ui->rotatePushButton->setEnabled(true);
        }
        else
        {
            ui->rotatePushButton->setEnabled(false);
        }

        if (ui->outputLineEdit->hasAcceptableInput())
        {
            ui->outputPushButton->setEnabled(true);
        }
        else
        {
            ui->outputPushButton->setEnabled(false);
        }
    }
    else
    {
        ui->movePushButton->setEnabled(false);
        ui->scalePushButton->setEnabled(false);
        ui->rotatePushButton->setEnabled(false);
        ui->outputPushButton->setEnabled(false);
    }
}

void MainWindow::on_inputPushButton_clicked()
{
    if (file_success == 1)
    {
        scene->clear();
    }

    int code_error = OK;
    QString filename = ui->inputLineEdit->text();
    QByteArray bytes = filename.toLatin1();
    char *str = bytes.data();
    parameters.filename = strdup(str);
    code_error = controller(*scene, parameters, LOAD);
    if (code_error == OK)
    {
        code_error = controller(*scene, parameters, DRAW);
        file_success = 1;
    }
    else
    {
        show_error(code_error);
    }
}

void MainWindow::show_error(int code_error)
{
    QString message = "";
    switch (code_error)
    {
    case ERR_OPEN:
        message = "Не удалось найти такой файл!";
        break;
    case ERR_READ:
        message = "Не удалось прочесть данные из файла, проверьте содержимое!";
        break;
    case ERR_MEMORY:
        message = "Произошла системная ошибка, перезапустите приложение или обратитесь в техническую поддержку!";
        break;
    case ERR_SAVE:
        message = "Не удалось записать данные в файл, попробуйте еще раз! Если ошибка повторяется, обратитесь в техническую поддержку!";
        break;
    case WARNING:
        break;
    case UNKNOWN_PROBLEM:
        message = "Критическая ошибка программы!";
        break;
    default:
        break;
    }
    if (message != "")
        QMessageBox::information(this, "Ошибка", message);
}

void MainWindow::on_rotatePushButton_clicked()
{
    int code_error = OK;
    scene->clear();
    QString entry_angle = ui->angleLineEdit->text();
    double angle = entry_angle.toDouble();
    parameters.angle = angle;
    if (ui->xRadioButton->isChecked())
    {
        code_error = controller(*scene, parameters, ROTATE_X);
    }
    else if (ui->yRadioButton->isChecked())
    {
        code_error = controller(*scene, parameters, ROTATE_Y);
    }
    else if (ui->zRadioButton->isChecked())
    {
        code_error = controller(*scene, parameters, ROTATE_Z);
    }

    if (code_error != OK) {
        show_error(code_error);
    }
    else
    {
        code_error = controller(*scene, parameters, DRAW);
    }
}

void MainWindow::on_movePushButton_clicked() {
    int code_error = OK;
    scene->clear();
    QString entry_x = ui->dxLineEdit->text();
    double dx = entry_x.toDouble();
    QString entry_y = ui->dyLineEdit->text();
    double dy = entry_y.toDouble();
    QString entry_z = ui->dzLineEdit->text();
    double dz = entry_z.toDouble();
    parameters.dx = dx;
    parameters.dy = dy;
    parameters.dz = dz;
    code_error = controller(*scene, parameters, MOVE);

    if (code_error != OK)
    {
        show_error(code_error);
    }
    else
    {
        code_error = controller(*scene, parameters, DRAW);
    }
}

void MainWindow::on_scalePushButton_clicked()
{
    int code_error = OK;
    scene->clear();
    QString entry_kx = ui->kxLineEdit->text();
    double kx = entry_kx.toDouble();
    QString entry_ky = ui->kyLineEdit->text();
    double ky = entry_ky.toDouble();
    QString entry_kz = ui->kzLineEdit->text();
    double kz = entry_kz.toDouble();
    parameters.kx = kx;
    parameters.ky = ky;
    parameters.kz = kz;
    code_error = controller(*scene, parameters, SCALE);

    if (code_error != OK)
    {
        show_error(code_error);
    }
    else
    {
        code_error = controller(*scene, parameters, DRAW);
    }
}

void MainWindow::on_outputPushButton_clicked()
{
    int code_error = OK;
    QString filename = ui->outputLineEdit->text();
    QByteArray bytes = filename.toLatin1();
    char *str = bytes.data();
    parameters.filename = strdup(str);
    code_error = controller(*scene, parameters, SAVE);
    code_error = controller(*scene, parameters, DRAW);
    if (code_error != OK)
    {
        code_error = controller(*scene, parameters, DRAW);
    }
    else
    {
        code_error = controller(*scene, parameters, DRAW);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int code_error = OK;
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Закрыть?",
                                                  "Уверены?",
                                                  QMessageBox::Yes|QMessageBox::No))
    {
        code_error = controller(*scene, parameters, FREE_MEMORY);
        event->accept();
    }
}
