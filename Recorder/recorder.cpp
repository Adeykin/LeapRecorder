#include "recorder.h"

#include <iostream>

Recorder::Recorder()
{

}

void Recorder::setFrame(const Leap::Frame frame)
{
    if(recordStarted)
    {
        record.push_back(frame);
    }
}

void Recorder::startRecord()
{
    recordStarted = true;
}

void Recorder::stopRecord()
{
    recordStarted = false;
}

void Recorder::clearRecord()
{
    record.clear();
}

std::list<Leap::Frame> Recorder::getRecord() const
{
    return record;
}

