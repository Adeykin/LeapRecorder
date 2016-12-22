#ifndef HANDSKELETONWIDGET_H
#define HANDSKELETONWIDGET_H

//#include <QGLWIdget>
#include <Leap.h>
#include <QtOpenGL/QGLWidget>
#include <memory>

class HandSkeletonWidget : public QGLWidget
{
public:
    HandSkeletonWidget(QWidget *parent);
    void setFrame(Leap::Frame frame);
protected:
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();

    void drawHand();
    void drawGrid();

    std::unique_ptr<Leap::Frame> lastFrame;
    bool updateFrame;
};

#endif // HANDSKELETONWIDGET_H
