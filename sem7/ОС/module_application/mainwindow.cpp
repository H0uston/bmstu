
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <fstream>
#include <QTimer>
#include "update_functions.h"

static const int info_update_gap = 1000;
static const int cpu_stats_gap = 300;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->update_info();
    QTimer *info_timer = new QTimer;
    connect(info_timer, SIGNAL(timeout()), this, SLOT(update_info()));
    info_timer->start(info_update_gap);

}

void MainWindow::update_info() {
    ui->host_name_label->setText("Имя компьютера: " + get_hostname());
    ui->user_name_label->setText("Имя пользователя: " + get_user_name());
    ui->uptime_label->setText("Время непрерывной работы: " + get_uptime());
    ui->cpu_model_label->setText("Модель центрального процессора: " + get_cpu_model());
    ui->cpu_frequency_label->setText("Частота центрального процессора: " + get_cpu_frequency() + " MHz");
    ui->cpu_load_progressbar->setValue(get_cpu_load(cpu_stats_gap));
    ui->total_memory_label->setText("Доступная оперативная память: " + get_available_memory());
    ui->busy_memory_lable->setText("Используемая оперативная память: " + get_busy_memory());
    ui->busy_memory_progressbar->setValue(get_memory_percentage());
}

MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::connect_module(const std::string& str_write, const std::string& filename, std::vector<std::string>& answer)
{
    std::ofstream fw;
    fw.open(filename);
    if(fw.is_open())
    {
        fw << str_write;
        qDebug() << "Успешно записано " << QString(str_write.data()) << " в " << QString(filename.data());
        fw.close();
    }
    else
        return -1;

    std::ifstream fr(filename);
    if(fr.is_open())
    {
        std::string line;
        bool eof = fr.eof();
        bool good = fr.good();
        bool bad = fr.bad();
        if (eof) {
            answer.push_back("No such ID!");
            return 0;
        }

        while (std::getline(fr, line) && line.length() != 0)
        {
           qDebug() << QString(line.data());
           answer.push_back(line);
        }
        fr.close();
        return 0;
    }
    return -1;


}

void MainWindow::on_btn_tree_clicked()
{
    std::vector<std::string> answer;
    std::string filename("/proc/mod_proc_tree");
    std::string str_write("tree");

    int res = this->connect_module(str_write, filename, answer);

    if (res == 0)
    {
        ui->tb_tree->clear();
        for(std::string s : answer)
        {
            ui->tb_tree->append(QString(s.data()));
        }
    }
    else
    {
        QMessageBox::warning(this, "Модуль не доступен",
            "Невозможно обратиться к модулю.\nВозможно, он не загружен\nили используется другим процессом");
    }

}

void MainWindow::on_btn_files_clicked()
{

    std::vector<std::string> answer;
    std::string filename("/proc/mod_proc_files");
    std::string str_write(std::to_string(ui->spb_files->value()));

    int res = this->connect_module(str_write, filename, answer);

    if (res == 0)
    {
        ui->tb_files->clear();
        for(std::string s : answer)
        {
              ui->tb_files->append(QString(s.data()));
        }
    }
    else
    {
        QMessageBox::warning(this, "Модуль не доступен",
            "Невозможно обратиться к модулю.\nВозможно, он не загружен\nили используется другим процессом");
    }
}

void MainWindow::on_btn_mem_clicked()
{
    std::vector<std::string> answer;
    std::string filename("/proc/mod_proc_mem");
    std::string str_write(std::to_string(ui->spb_mem->value()));

    int res = this->connect_module(str_write, filename, answer);

    if (res == 0)
    {
        ui->tb_mem->clear();
        for(std::string s : answer)
        {
              ui->tb_mem->append(QString(s.data()));
        }
    }
    else
    {
        QMessageBox::warning(this, "Модуль не доступен",
            "Невозможно обратиться к модулю.\nВозможно, он не загружен\nили используется другим процессом");
    }
}
