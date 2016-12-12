#include "mainwindow.h"
#include "handskeletonwidget.h"

#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setStyleSheet( "QWidget{ background-color : rgba( 160, 160, 160, 255); border-radius : 7px;  }" );
    //QLabel *label = new QLabel(this);
    handSkeletonWidget = new HandSkeletonWidget(this);
    //handSkeletonWidget->resize(200,200);    //QVBoxLayout *layout = new QVBoxLayout(this);
    //label->setText("Random String");
    //layout->addWidget(label);
    //setLayout(layout);
    this->setCentralWidget( handSkeletonWidget );
    resize(400,400);
    handSkeletonWidget->resize(400,400);
}

MainWindow::~MainWindow()
{
    delete handSkeletonWidget;
}
