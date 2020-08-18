#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setFixedSize(450,300);
    w.setWindowTitle("进制转换器");
    return a.exec();
}
