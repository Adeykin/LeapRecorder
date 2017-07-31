#ifndef MAINWINDOWMARK_H
#define MAINWINDOWMARK_H

#include <QMainWindow>

namespace Ui {
class MainWindowMarker;
}

class MainWindowMarker : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowMarker(QWidget *parent = 0);
    ~MainWindowMarker();

private:
    Ui::MainWindowMarker *ui;
};

#endif // MAINWINDOWMARK_H
