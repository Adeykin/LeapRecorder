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
    setFixedSize(1280, 600);
    //setBaseSize(1280, 600);
    QVBoxLayout *layout = new QVBoxLayout(central);
    QHBoxLayout *hLayout = new QHBoxLayout(central);
    central->setLayout(layout);
    this->setCentralWidget( central );

    layout->addLayout(hLayout);

    handSkeletonWidget = new HandSkeletonWidget(central);
    hLayout->addWidget(handSkeletonWidget);
    recorder = new Recorder();

    //cameraLabel = new QLabel();
    //cameraLabel->resize(640, 480);
    //hLayout->addWidget(cameraLabel);
    videoWidget = new VideoWidget(640, 240, central);
    hLayout->addWidget(videoWidget);

    imagesCheckbox = new QCheckBox("Write video", central);
    layout->addWidget(imagesCheckbox);

    recBut = new QPushButton("Rec");
    layout->addWidget(recBut);

    connect(recBut, SIGNAL(clicked()), this, SLOT(recClicked()));

    central->installEventFilter(this);
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
            int version = 0;
            if(imagesCheckbox->checkState() == Qt::Checked) {
                version = 1;
            }
            const int bufSize = 640*240;
            uint8_t zeroBuf[bufSize]; //size of Leap Motion IR image
            memset(zeroBuf, 0, bufSize);

            qDebug() << "Serialisation version: " << version << '\n';

            recorder->stopRecord();

            std::pair<std::list<Leap::Frame>, std::list<char>> recordPair = recorder->getRecord();

            qDebug() << "I have a record; Size " << recordPair.first.size() << " frames\n";

            recorder->clearRecord();

            QString fileName = QFileDialog::getSaveFileName(this, "Save file", ".gst", ".gst");
            qDebug() << fileName;

            std::ofstream file(fileName.toStdString().c_str(), std::ios::binary);
            file << "MN"; //Magic sequence
            file.put(version);
            for(auto it = recordPair.first.begin(); it != recordPair.first.end(); it++)
            {
                Leap::Frame& frame = *it;
                std::string serializedFrame = frame.serialize();

                //qDebug() << "frame: " << frame.id() << ' ' << frame.fingers().extended().count() << '\n';
                int32_t size = serializedFrame.size();
                file.write((char*)&size, 4);
                file.write(serializedFrame.c_str(), size);

                if(version == 1)
                {
                    if(frame.images().count() > 0)
                        file.write((char*)frame.images()[0].data(), bufSize);
                    else
                        file.write((char*)zeroBuf, bufSize);
                }
            }

            std::ofstream fileLabels((fileName.toStdString() + ".lbl").c_str(), std::ios::binary);
            for(char label: recordPair.second)
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
