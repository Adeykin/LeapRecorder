#ifndef SAMPLELISTINER_H
#define SAMPLELISTINER_H

#include "handskeletonwidget.h"
#include <Leap.h>


class SampleListiner : public Leap::Listener
{
public:
    SampleListiner(HandSkeletonWidget* widget);

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
private:
    HandSkeletonWidget* widget;
};

#endif // SAMPLELISTINER_H
