#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(w.width, w.height);
    w.setWindowTitle("植物大战僵尸");
    w.show();
    return a.exec();
}
