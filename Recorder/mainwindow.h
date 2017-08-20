#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <handskeletonwidget.h>
#include <recorder.h>

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
protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
private slots:
    //bool keypres(QKeyEvent *keyevent);
    void recClicked();
private:
    HandSkeletonWidget* handSkeletonWidget = nullptr;
    Recorder* recorder = nullptr;
    QPushButton* recBut;

    bool recordingNow = false;
};

#endif // MAINWINDOW_H
