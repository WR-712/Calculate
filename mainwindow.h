#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QButtonGroup>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QButtonGroup input;
    QButtonGroup output;
    QString data_input;
    QString data_output;
    int code_input;
    int code_resu;
    int start;
    QString resu;


    //计算器
    QString cal_x;
    QString cal_y;
    QString cal_recv;
    QString cal_deal;
    QString cal_res;

    QStringList stringlist;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    //进制转换
    void on_lineEdit_input_textChanged(const QString &arg1);
    void print_resu();
    void code_change();
    //计算器
    void on_btn_clear_clicked();


    void data_recv_guolu();
    void data_recv();
    void data_recv_deal();
    void resu_print();
    void data_input_print();
private slots:
    void on_qingchu_clicked();

private:
    Ui::MainWindow *ui;
     void system_init();
};

#endif // MAINWINDOW_H
