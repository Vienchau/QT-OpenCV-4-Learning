#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("QR CODE SCANNER");
    w.setWindowIcon(QIcon("D:\\MY_WORK\\tai_lieu\\logo\\Logo BK.png"));
    w.show();
    return a.exec();
}
