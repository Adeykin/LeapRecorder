#ifndef RECORDER_H
#define RECORDER_H

#include <list>
#include <Leap.h>

class Recorder
{
public:
    Recorder();

    void setFrame(const Leap::Frame frame);
    void startRecord();
    void stopRecord();
    void clearRecord();
    std::list<Leap::Frame> getRecord() const;
private:
    bool recordStarted = false;
    std::list<Leap::Frame> record;
};

#endif // RECORDER_H
