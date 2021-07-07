#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->drawLabel->setPalette(bg_colour);
    ui->drawLabel->setMouseTracking(true);
    scene = new QPixmap(500, 500);
    painter = new QPainter(scene);
    scene->fill(Qt::white);
    this->setMouseTracking(true);

    QRegExp check_double_number("^[-+]?(\\d+(\\.\\d*)?|\\.\\d+)$");
    QRegExpValidator *double_validator = new QRegExpValidator(check_double_number, this);
    ui->xLineEdit->setValidator(double_validator);
    ui->yLineEdit->setValidator(double_validator);

    ui->xLineEdit->setEnabled(false);
    ui->yLineEdit->setEnabled(false);
    ui->addPointPushButton->setEnabled(false);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);

    ui->borderColourFrame->setAutoFillBackground(true);
    ui->borderColourFrame->setPalette(Pal);
    Pal.setColor(QPalette::Background, Qt::red);

    ui->fillColourFrame->setAutoFillBackground(true);
    ui->fillColourFrame->setPalette(Pal);
    fill_colour = QColor(Qt::red);
    bg_colour = QColor(Qt::white);
    border_colour = QColor(Qt::black);

    Pal.setColor(QPalette::Background, Qt::white);
    ui->bgColourFrame->setAutoFillBackground(true);
    ui->bgColourFrame->setPalette(Pal);
}

void MainWindow::on_keyboardRadioButton_clicked()
{
    ui->xLineEdit->setEnabled(true);
    ui->yLineEdit->setEnabled(true);
    ui->addPointPushButton->setEnabled(true);
}

void MainWindow::on_mouseRadioButton_clicked()
{
    ui->xLineEdit->setEnabled(false);
    ui->yLineEdit->setEnabled(false);
    ui->addPointPushButton->setEnabled(false);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    edge_t edge;
    if (ui->mouseRadioButton->isChecked() && canvas_was_not_pushed)
    {
        painter->setPen(QPen(border_colour));
        double x = event->x();
        double y = event->y();
        if (x > 10 && y > 10 && x < 510 && y < 510)
        {
            if (first_click)
            {
                curr_x = x;
                curr_y = y;
                first_click = false;
            }
            if (event->button() == Qt::LeftButton)
            {
                if (event->modifiers() == Qt::ShiftModifier)
                {
                    if (fabs(prev_x - x) < fabs(prev_y - y))
                    {
                        x = prev_x;
                    }
                    else
                    {
                        y = prev_y;
                    }
                }
                painter->drawEllipse(x - OFFSET, y - OFFSET, 1, 1);
                if (prev_x != -1 && prev_y != -1)
                {
                    painter->drawLine(prev_x - OFFSET, prev_y - OFFSET, x - OFFSET, y - OFFSET);
                    edge.first_point_x = prev_x - OFFSET;
                    edge.first_point_y = prev_y - OFFSET;
                    edge.second_point_x = x - OFFSET;
                    edge.second_point_y = y - OFFSET;
                }
                prev_x = x;
                prev_y = y;
            }
            else if (event->button() == Qt::RightButton)
            {
                if (prev_x != -1 && prev_y != -1)
                {
                    painter->drawLine(prev_x - OFFSET, prev_y - OFFSET, curr_x - OFFSET, curr_y - OFFSET);
                    edge.first_point_x = prev_x - OFFSET;
                    edge.first_point_y = prev_y - OFFSET;
                    edge.second_point_x = curr_x - OFFSET;
                    edge.second_point_y = curr_y - OFFSET;

                    prev_x = -1;
                    prev_y = -1;
                    first_click = true;
                }
            }
            all_edges.append(edge);
        }
        ui->drawLabel->setPixmap(*scene);
    }
    else
    {
        double x = event->x();
        double y = event->y();
        if (x > 10 && y > 10 && x < 510 && y < 510)
        {
            QMessageBox msgBox;
            msgBox.setText("Warning!");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setInformativeText("Для ввода точки с мыши выбирите соответствующую опцию");
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
    }
}

void MainWindow::on_borderColourPushButton_clicked()
{
    border_colour = QColorDialog::getColor(Qt::white, this);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, border_colour);
    ui->borderColourFrame->setAutoFillBackground(true);
    ui->borderColourFrame->setPalette(Pal);
    ui->borderColourFrame->show();
}

void MainWindow::on_fillColourPushButton_clicked()
{
    fill_colour = QColorDialog::getColor(Qt::red, this);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, fill_colour);
    ui->fillColourFrame->setAutoFillBackground(true);
    ui->fillColourFrame->setPalette(Pal);
    ui->fillColourFrame->show();
}

void MainWindow::on_bgColourPushButton_clicked()
{
    bg_colour = QColorDialog::getColor(Qt::white, this);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, bg_colour);
    ui->bgColourFrame->setAutoFillBackground(true);
    ui->bgColourFrame->setPalette(Pal);
    ui->bgColourFrame->show();
    change_background();
}

void MainWindow::on_clearPushButton_clicked()
{
    delete painter;
    delete scene;
    all_edges.clear();
    ui->drawLabel->clear();
    scene = new QPixmap(510, 510);
    scene->fill(QColor(bg_colour));
    painter = new QPainter(scene);
    ui->drawLabel->setPixmap(*scene);
    prev_x = -1;
    prev_y = -1;
    canvas_was_not_pushed = true;
    first_click = true;
}

void MainWindow::change_background()
{
    scene->fill(QColor(bg_colour));

    for (int i = 0; i < all_edges.size(); i++)
    {
        painter->drawLine(all_edges[i].first_point_x, all_edges[i].first_point_y,
                          all_edges[i].second_point_x, all_edges[i].second_point_y);
    }
    ui->drawLabel->setPixmap(*scene);
}

void MainWindow::on_addPointPushButton_clicked()
{

    bool ok1 = true, ok2 = true;
    QString x1_s = ui->xLineEdit->text();
    QString y1_s = ui->yLineEdit->text();
    double x = x1_s.toDouble(&ok1);
    double y = y1_s.toDouble(&ok2);
    edge_t edge;
    if (ui->keyboardRadioButton->isChecked())
    {
        if (ok1 && ok2)
        {
            painter->setPen(QColor(border_colour));
            painter->drawEllipse(x, y, 1, 1);
            if (prev_x != -1 && prev_y != -1)
            {
                edge.first_point_x = prev_x - OFFSET;
                edge.first_point_y = prev_y - OFFSET;
                edge.second_point_x = x;
                edge.second_point_y = y;
                painter->drawLine(prev_x - OFFSET, prev_y - OFFSET, x, y);
            }
            // Для того, чтобы при переключении способов рисования, можно было продолжить отрисовку
            prev_x = x + OFFSET;
            prev_y = y + OFFSET;

            ui->drawLabel->setPixmap(*scene);
            if (first_click)
            {
                curr_x = x + OFFSET;
                curr_y = y + OFFSET;
                first_click = false;
            }
            all_edges.append(edge);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Подождите!");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setInformativeText("Введены неверные параметры");
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
    }
}

void MainWindow::on_closePushButton_clicked()
{
    edge_t edge;
    if (prev_x != -1 && prev_y != -1)
    {
        edge.first_point_x = prev_x - OFFSET;
        edge.second_point_x = curr_x - OFFSET;
        edge.first_point_y = prev_y - OFFSET;
        edge.second_point_y = curr_y - OFFSET;
        painter->drawLine(prev_x - OFFSET, prev_y - OFFSET, curr_x - OFFSET, curr_y - OFFSET);
        prev_x = -1;
        prev_y = -1;
        first_click = true;
        all_edges.append(edge);
    }
    ui->drawLabel->setPixmap(*scene);
}


void MainWindow::on_fillPushButton_clicked()
{
    // needed at least 2 points
    if (all_edges.size() > 2)
    {

        double x_max = 0;
        double y_min = all_edges[1].first_point_y;
        double y_max = 0;
        for (int i = 1; i < all_edges.size(); i++)
        {
            if (all_edges[i].first_point_x > x_max)
                x_max = all_edges[i].first_point_x;

            if (all_edges[i].first_point_y > y_max)
                y_max = all_edges[i].first_point_y;

            if (all_edges[i].first_point_y < y_min && all_edges[i].first_point_y > 0)
                y_min = all_edges[i].first_point_y;
        }

        for (int i = 1; i < all_edges.size(); i++)
        {


            QImage image = scene->toImage();

            double x1e = all_edges[i].first_point_x;
            double x2e = all_edges[i].second_point_x;
            double y1e = all_edges[i].first_point_y;
            double y2e = all_edges[i].second_point_y;

            // Если горизонтальная
            if (fabs(y1e - y2e) < EPS)
                continue;

            if (y1e > y2e)
            {
                swap(y1e, y2e);
                swap(x1e, x2e);
            }

            double y = y1e;
            double end_y = y2e;
            double dx = x2e - x1e;
            double dy = y2e - y1e;
            double k = dx / dy;
            double start_x = x1e;
            while (y < end_y)
            {
                double x = start_x;
                while (x < x_max)
                {
                    painter->setPen(QPen(border_colour));
                    QColor color = image.pixelColor(QPoint(x, y));

                    if (color == bg_colour)
                    {
                        painter->setPen(QColor(fill_colour));
                    }
                    else if (color == fill_colour)
                    {
                        painter->setPen(QColor(bg_colour));
                    }
                    painter->drawPoint(x, y);
                    x++;

                }
                start_x += k;
                y++;

                if (ui->checkBox->isChecked())
                {
                    const int value = ui->spinBox->value();
                    sleepFeature(value);
                }

                ui->drawLabel->setPixmap(*scene);
            }
        }
    }
}

void sleepFeature(const int &time)
{
    QTime end = QTime::currentTime().addMSecs(time);
    while (QTime::currentTime() < end)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
