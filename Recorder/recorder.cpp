#include "recorder.h"

#include <iostream>
#include <QDebug>

Recorder::Recorder()
{
    //initing letter map
    letterMap['f'] = 1;
    letterMap[','] = 2;
    letterMap['d'] = 3;
    letterMap['u'] = 4;
    letterMap['l'] = 5;
    letterMap['t'] = 6;
    letterMap[';'] = 7;
    letterMap['p'] = 8;
    letterMap['b'] = 9;
    letterMap['q'] = 10;
    letterMap['r'] = 11;
    letterMap['k'] = 12;
    letterMap['v'] = 13;
    letterMap['y'] = 14;
    letterMap['j'] = 15;
    letterMap['g'] = 16;
    letterMap['h'] = 17;
    letterMap['c'] = 18;
    letterMap['n'] = 19;
    letterMap['e'] = 20;
    letterMap['a'] = 21;
    letterMap['['] = 22;
    letterMap['w'] = 23;
    letterMap['x'] = 24;
    letterMap['i'] = 25;
    letterMap['o'] = 26;
    letterMap[']'] = 27;
    letterMap['s'] = 28;
    letterMap['m'] = 29;
    letterMap['\''] = 30;
    letterMap['.'] = 31;
    letterMap['z'] = 32;
}

void Recorder::setFrame(const Leap::Frame frame)
{
    if(recordStarted)
    {
        record.push_back(frame);
        labels.push_back(currentLabel);
    }
}

void Recorder::startLabel(char label)
{
    currentLabel = letterMap[label];
}

void Recorder::stopLabel()
{
    currentLabel = 0;
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
    labels.clear();
}

std::pair<std::list<Leap::Frame>, std::list<char>> Recorder::getRecord() const
{
    return std::make_pair(record, labels);
}

