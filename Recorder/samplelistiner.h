#ifndef SAMPLELISTINER_H
#define SAMPLELISTINER_H

#include "handskeletonwidget.h"
#include "recorder.h"
#include "framehandler.h"
#include <Leap.h>
#include <QLabel>


class SampleListiner : public Leap::Listener
{
public:
    SampleListiner();

    virtual void onInit(const Leap::Controller&);
    virtual void onConnect(const Leap::Controller&);
    virtual void onDisconnect(const Leap::Controller&);
    virtual void onExit(const Leap::Controller&);
    virtual void onFrame(const Leap::Controller&);
    virtual void onFocusGained(const Leap::Controller&);
    virtual void onFocusLost(const Leap::Controller&);
    virtual void onDeviceChange(const Leap::Controller&);
    virtual void onServiceConnect(const Leap::Controller&);
    virtual void onServiceDisconnect(const Leap::Controller&);

    void addFrameHandler(IFrameHanler* framehandler);
private:
    std::vector<IFrameHanler*> frameHandlers;
};

#endif // SAMPLELISTINER_H
