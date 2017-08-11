#ifndef SEQUENCEMARKER_H
#define SEQUENCEMARKER_H

#include <QString>
#include <QtGlobal>
#include <list>
#include <cmath>
#include <Leap.h>

class SequenceMarker
{
public:
    static SequenceMarker* createSequenceMaerker(QString fileName);

    int getCurrentIndex() const {return index;}
    int getMaxIndex() const {return frames.size();}
    char next() { return labels[index = qMin((size_t)index+1, frames.size()-1)]; } ;
    char prev() { return labels[index = qMax(0, index-1)]; };
    char getLabel() const { return getLabel(index); }
    char getLabel(int index) const { return labels[index]; }
    void setLabel(char label) { labels[index] = label; }

    Leap::Frame getFrame() const {return frames[index];}

    int save(QString);

private:
    SequenceMarker();
    int load(QString);

    std::vector<Leap::Frame> frames;
    std::vector<char> labels;
    int index = 0;
};

#endif // SEQUENCEMARKER_H
