#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

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
    void update_info();

    void on_btn_tree_clicked();

    void on_btn_files_clicked();

    void on_btn_mem_clicked();

private:
    int connect_module(const std::string& str_write, const std::string& filename, std::vector<std::string>& answer);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
