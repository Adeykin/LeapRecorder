#include "mainwindow.h"
#include "handskeletonwidget.h"

#include <iostream>
#include <vector>
#include <fstream>

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    central->setLayout(layout);
    this->setCentralWidget( central );

    handSkeletonWidget = new HandSkeletonWidget(central);
    layout->addWidget(handSkeletonWidget);
    recorder = new Recorder();

    recBut = new QPushButton("Rec");
    layout->addWidget(recBut);

    connect(recBut, SIGNAL(clicked()), this, SLOT(recClicked()));

    central->installEventFilter(this);

    resize(400,400);
}

MainWindow::~MainWindow()
{
    delete handSkeletonWidget;
    delete recorder;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    recorder->startLabel( (char)e->text()[0].unicode() );
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    recorder->stopLabel();
}

void MainWindow::recClicked()
{
    if(recordingNow)
    {
        recBut->setText("Rec");
        recordingNow = false;

        if(recorder)
        {
            recorder->stopRecord();

            std::pair<std::list<Leap::Frame>, std::list<char>> recordPair = recorder->getRecord();

            qDebug() << "I have a record; Size " << recordPair.first.size() << " frames\n";

            recorder->clearRecord();

            QString fileName = QFileDialog::getSaveFileName(this, "Save file", ".gst", ".gst");
            qDebug() << fileName;

            std::ofstream file(fileName.toStdString().c_str(), std::ios::binary);
            for(auto it = recordPair.first.begin(); it != recordPair.first.end(); it++)
            {
                Leap::Frame& frame = *it;
                std::string serializedFrame = frame.serialize();

                //qDebug() << "frame: " << frame.id() << ' ' << frame.fingers().extended().count() << '\n';
                int32_t size = serializedFrame.size();
                file.write((char*)&size, 4);
                file.write(serializedFrame.c_str(), size);
            }

            std::ofstream fileLabels((fileName.toStdString() + ".lbl").c_str(), std::ios::binary);
            for(char label: recordPair.second)
                //fileLabels.write( &label, 1);
                fileLabels.put(label);
        }
    }
    else
    {
        recBut->setText("Stop");
        recordingNow = true;

        if(recorder)
            recorder->startRecord();
    }
}
