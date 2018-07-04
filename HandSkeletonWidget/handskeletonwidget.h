#ifndef HANDSKELETONWIDGET_H
#define HANDSKELETONWIDGET_H

//#include <QGLWIdget>
#include <Leap.h>
#include <QtOpenGL/QGLWidget>
#include <memory>
#include "framehandler.h"

class HandSkeletonWidget : public QGLWidget, public IFrameHanler
{
    //Q_OBJECT
public:
    HandSkeletonWidget(QWidget *parent);
    void setFrame(const Leap::Frame& frame) override;
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
