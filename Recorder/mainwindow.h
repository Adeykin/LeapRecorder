#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <handskeletonwidget.h>
#include <recorder.h>
#include <videowidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    HandSkeletonWidget* getHandSkeletonWidget() const
        { return handSkeletonWidget; }
    Recorder* getRecorder() const
        { return recorder; }
    VideoWidget* getVideoWidget() const
        { return videoWidget; }
protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
private slots:
    //bool keypres(QKeyEvent *keyevent);
    void recClicked();
private:
    HandSkeletonWidget* handSkeletonWidget = nullptr;
    VideoWidget* videoWidget = nullptr;
    Recorder* recorder = nullptr;
    QPushButton* recBut;
    QPixmap* pixmap;

    bool recordingNow = false;
};

#endif // MAINWINDOW_H
