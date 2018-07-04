#ifndef FRAMEHANDLER_H
#define FRAMEHANDLER_H

#include <Leap.h>

class IFrameHanler {
public:
    virtual void setFrame(const Leap::Frame& frame) = 0;
    virtual ~IFrameHanler() {};
};

#endif // FRAMEHANDLER_H

