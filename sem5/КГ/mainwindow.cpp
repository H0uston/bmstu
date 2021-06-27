#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    render_manager = new Render_manager(this);
    mm = new Model_manager();
    setMouseTracking(true);

    timerForTrain = new QTimer();
    timerForTrain->setSingleShot(true);
    connect(timerForTrain, SIGNAL(timeout()), this, SLOT(MoveTrain()));

    loadModels();

    QRegExp check = QRegExp("[-+]?(\\d+(\\.\\d*)?|\\.\\d+)$");
    QRegExpValidator *valid_double = new QRegExpValidator(check, this);

    ui->dxLineEdit->setValidator(valid_double);
    ui->dyLineEdit->setValidator(valid_double);
    ui->stopPushButton->setEnabled(false);
    render_manager->render_models();
}

void MainWindow::loadModels()
{
    QString file_name = "locomotive.obj";
    Parser tmp;
    Model model_1 = tmp.load_model(file_name);
    mm->rotate_x(model_1, -90);
    mm->move(model_1, Point3D(-80, 4, 0));
    render_manager->set_locomotive(model_1);

    file_name = "carriage.obj";
    Model model_2 = tmp.load_model(file_name);
    mm->rotate_x(model_2, -90);
    mm->move(model_2, Point3D(-80, 5, 0));
    render_manager->set_carriage(model_2);

    file_name = "tree_low.obj";
    Model model_3 = tmp.load_model(file_name);
    mm->rotate_x(model_3, -90);
    render_manager->set_tree(model_3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startPushButton_clicked()
{
    if (moving_on)
        return;
    if (!stopped)
        render_manager->spawn_train(ui->spinBox->value());
    ui->startPushButton->setEnabled(false);
    ui->stopPushButton->setEnabled(true);
    ui->addTreePushButton->setEnabled(false);
    ui->spinBox->setEnabled(false);
    ui->addTreesPushButton->setEnabled(false);
    moving_on = true;
    timer = 0;
    timerForTrain->start(timer);
}

void MainWindow::on_stopPushButton_clicked()
{
    moving_on = false;
    stopped = true;
    timer = 0;
    ui->startPushButton->setEnabled(true);
    ui->stopPushButton->setEnabled(false);
}

void MainWindow::on_addTreePushButton_clicked()
{
    if (moving_on)
        return;
    Model tree = render_manager->get_tree_model();
    QString x = ui->dxLineEdit->text();
    QString y = ui->dyLineEdit->text();

    if (x == "" || y == "")
    {
        QMessageBox messageBox;
        messageBox.information(0,"Ошибка","Перед размещением дерева нужно заполнить поля x и у!");
        messageBox.setFixedSize(500,200);
        return;
    }
    int value = ui->scaleBox->value();
    double dx = x.toDouble();
    double dy = y.toDouble();
    double koef = (value + 3) / 10.0;
    if (!(dx > -270 && dx < 270 && dy > -270 && dy < 270))
    {
        QMessageBox messageBox;
        messageBox.information(0,"Ошибка","Пожалуйста, размещайте деревья только на поверхности земли!");
        messageBox.setFixedSize(500,200);
        return;
    }
    else if (dy > -19 && dy < 25)
    {
        QMessageBox messageBox;
        messageBox.information(0,"Ошибка","Размещение деревьев на железной дороге запрещено!");
        messageBox.setFixedSize(500,200);
        return;
    }
    mm->scale(tree, koef);
    if (value == 1)
    {
        dx *= 1.26;
        dy *= 1.26;
    }
    else if (value == 3)
    {
        dx *= 0.84;
        dy *= 0.84;
    }
    mm->move(tree, Point3D(-dx, 0, -dy));
    render_manager->append_model(tree);
    render_manager->camera->rotate(Point3D(0,0,0));
    render_manager->render_models();
}

void MainWindow::on_addTreesPushButton_clicked()
{
    if (moving_on)
        return;
    ui->addTreesPushButton->setEnabled(false);
    ui->startPushButton->setEnabled(false);
    ui->stopPushButton->setEnabled(false);
    ui->spinBox->setEnabled(false);
    ui->quitAddTreesPushButton->setEnabled(true);

    old_attr = render_manager->camera->get_attributes();
    CameraAttributes new_attributes
    {
        Point3D(0,50,0),                                                   // position
        -90,                                                                // yaw
        -180,                                                                  // pitch
        Point3D(0,1,0),                                                     // top
        {90, 0.1, 1000, WIDGET_WIDTH / static_cast<double>(WIDGET_HEIGHT)}  // frustrum
    };
    render_manager->camera->set_attributes(new_attributes);
    add_tree_mode = true;
    render_manager->camera->rotate(Point3D(0,0,0));
    render_manager->render_models();
}

void MainWindow::on_quitAddTreesPushButton_clicked()
{
    if (!stopped)
    {
        ui->addTreesPushButton->setEnabled(true);
        ui->startPushButton->setEnabled(true);
        ui->spinBox->setEnabled(true);
        ui->quitAddTreesPushButton->setEnabled(false);
    }
    else
    {
        ui->stopPushButton->setEnabled(true);
        ui->addTreesPushButton->setEnabled(true);
        ui->quitAddTreesPushButton->setEnabled(false);
    }

    render_manager->camera->set_attributes(old_attr);
    render_manager->render_models();
    std::vector<Train> train = render_manager->get_train();
    for (size_t i = 0; i < train.size(); i++)
    {
        if ((train[i].get_center().get_x() + train[i].get_translation().get_x()) > render_manager->length + 10 ||
                (train[i].get_center().get_x() + train[i].get_translation().get_x()) < -render_manager->length - 10)
        {
            continue;
        }
        else
        {
            render_manager->render_train(train[i]);
        }
    }
    add_tree_mode = false;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (add_tree_mode)
        return;

    if (event->key() == Qt::Key_Escape)
    {
        ui->label_3->setFocusPolicy(Qt::WheelFocus);
        ui->label_3->setFocus(Qt::OtherFocusReason);
    }

    Model_manager mm;
    if (event->key() == Qt::Key_A)
    {
        camera_direction_movement cmm = {false, false, false, true, false, false};
        render_manager->camera->move_to(cmm);
    }
    else if (event->key() == Qt::Key_D)
    {
        camera_direction_movement cmm = {false, false, true, false, false, false};
        render_manager->camera->move_to(cmm);
    }
    else if (event->key() == Qt::Key_W)
    {
        camera_direction_movement cmm = {true, false, false, false, false, false};
        render_manager->camera->move_to(cmm);
    }
    else if (event->key() == Qt::Key_S)
    {
        camera_direction_movement cmm = {false, true, false, false, false, false};
        render_manager->camera->move_to(cmm);
    }
    else if (event->key() == Qt::Key_Q)
    {
        camera_direction_movement cmm = {false, false, false, false, true, false};
        render_manager->camera->move_to(cmm);
    }
    else if (event->key() == Qt::Key_E)
    {
        camera_direction_movement cmm = {false, false, false, false, false, true};
        render_manager->camera->move_to(cmm);
    }
    else if (event->key() == Qt::Key_Left)
    {
        render_manager->camera->rotate(Point3D(5, 0, 0));
    }
    else if (event->key() == Qt::Key_Right)
    {
        render_manager->camera->rotate(Point3D(-5, 0, 0));
    }
    else if (event->key() == Qt::Key_Up)
    {
        render_manager->camera->rotate(Point3D(0, 5, 0));
    }
    else if (event->key() == Qt::Key_Down)
    {
        render_manager->camera->rotate(Point3D(0, -5, 0));
    }
    render_manager->render_models();
    std::vector<Train> train = render_manager->get_train();
    for (size_t i = 0; i < train.size(); i++)
    {
        if ((train[i].get_center().get_x() + train[i].get_translation().get_x()) > render_manager->length + 10 ||
                (train[i].get_center().get_x() + train[i].get_translation().get_x()) < -render_manager->length - 10)
        {
            continue;
        }
        else
        {
            render_manager->render_train(train[i]);
        }
    }

}

void MainWindow::MoveTrain()
{
    render_manager->render_models();
    move_and_render_train();

    if (!timerForTrain->isActive())
    {
        if (moving_on)
        {
            timerForTrain->start(timer);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (add_tree_mode)
    {
        double x = event->x(), y = event->y();
        if (x < 20 || y < 20 || x > WIDGET_WIDTH + 20 || y > WIDGET_HEIGHT + 20)
            return;
        x = x - 20 - WIDGET_CENTER_WIDTH;
        y = y - 20 - WIDGET_CENTER_HEIGHT;
        if (x > -270 && x < 270 && y > -270 && y < 270)
        {
            if (y > -19 && y < 25)
            {
                QMessageBox messageBox;
                messageBox.information(0,"Ошибка","Размещение деревьев на железной дороге запрещено!");
                messageBox.setFixedSize(500,200);
                return;
            }

            double val = 1 / tan((90 / 2) * (M_PI / 180.0));
            x *= val / (WIDGET_WIDTH / static_cast<double>(WIDGET_HEIGHT)) * (2.0 / 3.0);
            y *= val / (WIDGET_WIDTH / static_cast<double>(WIDGET_HEIGHT)) * (2.0 / 3.0);
            ui->dxLineEdit->setText(QString::number(round(x)));
            ui->dyLineEdit->setText(QString::number(round(-y)));
        }
        else
        {
            QMessageBox messageBox;
            messageBox.information(0,"Ошибка","Пожалуйста, размещайте деревья только на поверхности земли!");
            messageBox.setFixedSize(500,200);
            return;
        }
    }
}

void MainWindow::end_of_movement()
{
    timer = 1;
    std::vector<Train>& train = render_manager->get_train();
    int count = train.size();
    double move_it = -1 * count * render_manager->length + 10;
    train[0].set_translation(Point3D(-80, 4, 0));
    for (size_t j = 1; j < count; j++)
    {
        train.pop_back();
    }
    moving_on = false;
    stopped = false;
    ui->startPushButton->setEnabled(true);
    ui->addTreePushButton->setEnabled(true);
    ui->spinBox->setEnabled(true);
    ui->addTreesPushButton->setEnabled(true);
}

void MainWindow::move_and_render_train()
{
    std::vector<Train>& train = render_manager->get_train();
    size_t count = train.size();
    for (size_t i = 0; i < count; i++)
    {
        mm->move(train[i], Point3D(1, 0, 0));
        if ((train[i].get_center().get_x() + train[i].get_translation().get_x()) < -render_manager->length - 10)
        {
            continue;
        }
        else if ((train[i].get_center().get_x() + train[i].get_translation().get_x()) > render_manager->length + 15)
        {
            if (i == count - 1)
            {
                end_of_movement();
                return;
            }
            else
                continue;
        }
        render_manager->render_train(train[i]);
        train[i].rotate_wheels();
    }
}
