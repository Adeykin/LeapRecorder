#include "mainwindowmarker.h"
#include "ui_mainwindow.h"

MainWindowMarker::MainWindowMarker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowMarker)
{
    ui->setupUi(this);
}

MainWindowMarker::~MainWindowMarker()
{
    delete ui;
}
