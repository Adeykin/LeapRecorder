#include "mainwindow.h"
#include <QApplication>
#include <Leap.h>

#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Leap::Controller controller;

    w.show();

    return a.exec();
}

