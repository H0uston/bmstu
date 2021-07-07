#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    paint_widget = new PaintWidget(this);
    QRegExp check("[-+]?\\d+$");
    QRegExpValidator *valid = new QRegExpValidator(check, this);
    ui->addPointButton->setEnabled(false);
    ui->lineEditX->setValidator(valid);
    ui->lineEditY->setValidator(valid);

    QPalette Pal(palette());

    Pal.setColor(QPalette::Background, Qt::white);
    ui->BGFrame->setAutoFillBackground(true);
    ui->BGFrame->setPalette(Pal);

    Pal.setColor(QPalette::Background, Qt::black);
    ui->segmentFrame->setAutoFillBackground(true);
    ui->segmentFrame->setPalette(Pal);

    Pal.setColor(QPalette::Background, Qt::blue);
    ui->cutterFrame->setAutoFillBackground(true);
    ui->cutterFrame->setPalette(Pal);

    Pal.setColor(QPalette::Background, Qt::red);
    ui->cutFrame->setAutoFillBackground(true);
    ui->cutFrame->setPalette(Pal);

    connect(ui->lineEditX, SIGNAL(textChanged(QString)), this, SLOT(addPointEnabled()));
    connect(ui->lineEditY, SIGNAL(textChanged(QString)), this, SLOT(addPointEnabled()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPointEnabled()
{
    enable_add = ui->lineEditX->hasAcceptableInput() &&
                  ui->lineEditY->hasAcceptableInput();
    ui->addPointButton->setEnabled(enable_add);
}

void MainWindow::on_addPointButton_clicked()
{
    QString tmp;
    QPoint cur_point;
    tmp = ui->lineEditX->text();
    cur_point.setX(tmp.toInt());
    tmp = ui->lineEditY->text();
    cur_point.setY(tmp.toInt());
    // paint_widget->drawByButton(cur_point);
}

void MainWindow::on_changeBGColourButton_clicked()
{
    QColor colour = QColorDialog::getColor(Qt::white, this,"Выберите цвет");
    if (colour.isValid())
    {
        QPalette palette;
        palette.setColor(QPalette::Background, colour);
        ui->BGFrame->setPalette(palette);
        paint_widget->setBGColour(colour);
    }
}

void MainWindow::on_changeSegmentColourButton_clicked()
{
    QColor colour = QColorDialog::getColor(Qt::white, this,"Выберите цвет");
    if (colour.isValid())
    {
        QPalette palette;
        palette.setColor(QPalette::Background, colour);
        ui->segmentFrame->setPalette(palette);
        paint_widget->setSegmentColour(colour);
    }
}

void MainWindow::on_changeCutterColourButton_clicked()
{
    QColor colour = QColorDialog::getColor(Qt::white, this,"Выберите цвет");
    if (colour.isValid())
    {
        QPalette palette;
        palette.setColor(QPalette::Background, colour);
        ui->cutterFrame->setPalette(palette);
        paint_widget->setCutterColour(colour);
    }
}

void MainWindow::on_changeCutColourButton_clicked()
{
    QColor colour = QColorDialog::getColor(Qt::white, this,"Выберите цвет");
    if (colour.isValid())
    {
        QPalette palette;
        palette.setColor(QPalette::Background, colour);
        ui->cutFrame->setPalette(palette);
        paint_widget->setCutColour(colour);
    }
}

void MainWindow::on_cutButton_clicked()
{
    paint_widget->cutSegments();
}

void MainWindow::on_clearButton_clicked()
{
    paint_widget->clear();
}

void MainWindow::on_clearCutterButton_clicked()
{
    paint_widget->clearCutter();
}

void MainWindow::on_segmentRadioButton_clicked()
{
    paint_widget->setDrawSegmentMode();
}

void MainWindow::on_cutterRadioButton_clicked()
{
    paint_widget->setDrawCutterMode();
}
