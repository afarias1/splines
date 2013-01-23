#include "mainwindow.h"
#include <QApplication>
#include <QGLFormat>

int main(int argc, char *argv[])
{
    /*Set format before initializing application*/
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
