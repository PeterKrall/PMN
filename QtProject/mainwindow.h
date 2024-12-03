#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bt_exit_clicked();

    void on_bt_go_clicked();

    void on_bt_select_output_directory_clicked();

private:
    Ui::MainWindow *ui;
    double get_double(QLineEdit*);
    int get_int(QLineEdit*);
};
#endif // MAINWINDOW_H
