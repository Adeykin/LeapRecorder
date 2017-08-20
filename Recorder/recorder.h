#ifndef RECORDER_H
#define RECORDER_H

#include <list>
#include <Leap.h>

class Recorder
{
public:
    Recorder();

    void setFrame(const Leap::Frame frame);
    void startLabel(char label);
    void stopLabel();
    void startRecord();
    void stopRecord();
    void clearRecord();
    std::pair<std::list<Leap::Frame>, std::list<char>> getRecord() const;
private:
    bool recordStarted = false;
    std::list<Leap::Frame> record;
    std::list<char> labels;

    char currentLabel = 0;

    char letterMap[256];
};

#endif // RECORDER_H
