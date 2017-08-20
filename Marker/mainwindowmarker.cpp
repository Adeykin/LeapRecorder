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

        if(fileName == QString()) //Cancel button was pressed
        {
            exit(0);
        }

        seqMarker = SequenceMarker::createSequenceMaerker(fileName);
    }
    while(!seqMarker);

    //ui->horizontalSlider->setTickInterval( seqMarker->getMaxIndex() );
    ui->horizontalSlider->setRange(0, seqMarker->getMaxIndex());
    updateUI();
}

void MainWindowMarker::updateUI()
{
    HandSkeletonWidget* skeletWidget = (HandSkeletonWidget*)ui->widget;

    //Leap::Frame frame = seqMarker->getFrame();
    skeletWidget->setFrame( seqMarker->getFrame() );

    status->setText( QString().setNum(seqMarker->getCurrentIndex()) + "/" + QString().setNum(seqMarker->getMaxIndex()) );
    ui->actualLatter->setText( QString().setNum((int)seqMarker->getLabel()) );

    ui->horizontalSlider->setValue( seqMarker->getCurrentIndex() );
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

void MainWindowMarker::on_actionSave_triggered()
{
    seqMarker->save();
}

void MainWindowMarker::on_horizontalSlider_valueChanged(int value)
{
    seqMarker->setIndex(value);
    updateUI();
}
