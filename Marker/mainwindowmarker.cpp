#include "mainwindowmarker.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <QTimer>

MainWindowMarker::MainWindowMarker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowMarker),
    status(new QLabel)
{
    ui->setupUi(this);

    QTimer::singleShot(0, this, SLOT(appReady())); //GUI is ready event

    ui->statusbar->addWidget( status );

    /*QFileDialog d;
    d.setWindowTitle("dialog");
    d.exec();*/
}

MainWindowMarker::~MainWindowMarker()
{
    delete ui;
}

void MainWindowMarker::appReady() //slot
{
    do {
        QString fileName = QFileDialog::getOpenFileName(NULL);
        qDebug() << "Opening file: " << fileName;

        seqMarker = SequenceMarker::createSequenceMaerker(fileName);
    }
    while(!seqMarker);

    updateUI();
}

void MainWindowMarker::updateUI()
{
    HandSkeletonWidget* skeletWidget = (HandSkeletonWidget*)ui->widget;

    //Leap::Frame frame = seqMarker->getFrame();
    skeletWidget->setFrame( seqMarker->getFrame() );

    status->setText( QString().setNum(seqMarker->getCurrentIndex()) + "/" + QString().setNum(seqMarker->getMaxIndex()) );
    ui->actualLatter->setText( QString().setNum((int)seqMarker->getLabel()) );
}

void MainWindowMarker::on_nextButton_clicked()
{
    seqMarker->next();
    updateUI();
}

void MainWindowMarker::on_prevButton_clicked()
{
    seqMarker->prev();
    updateUI();
}

void MainWindowMarker::on_writePrev_clicked()
{
    int label = ui->latter->text().toInt();
    seqMarker->setLabel(label);
    seqMarker->prev();
    updateUI();
}

void MainWindowMarker::on_writeNext_clicked()
{
    int label = ui->latter->text().toInt();
    seqMarker->setLabel(label);
    seqMarker->next();
    updateUI();
}
