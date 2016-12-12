#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <handskeletonwidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    HandSkeletonWidget* getHandSkeletonWidget()
        { return handSkeletonWidget; }
private:
    HandSkeletonWidget* handSkeletonWidget;
};

#endif // MAINWINDOW_H
