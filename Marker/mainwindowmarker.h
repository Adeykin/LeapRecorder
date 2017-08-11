#ifndef MAINWINDOWMARK_H
#define MAINWINDOWMARK_H

#include <QMainWindow>
#include <QLabel>
#include "sequencemarker.h"

namespace Ui {
class MainWindowMarker;
}

class MainWindowMarker : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowMarker(QWidget *parent = 0);
    ~MainWindowMarker();

public slots:
    void appReady();

private slots:
    void on_nextButton_clicked();

    void on_prevButton_clicked();

    void on_writePrev_clicked();

    void on_writeNext_clicked();

private:
    void updateUI();

    Ui::MainWindowMarker *ui;

    SequenceMarker* seqMarker = nullptr;

    QLabel* status = nullptr;
};

#endif // MAINWINDOWMARK_H
