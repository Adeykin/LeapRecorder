#ifndef SEQUENCEMARKER_H
#define SEQUENCEMARKER_H

#include <QString>
#include <QtGlobal>
#include <QImage>
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
    void setIndex(int index) { this->index = qMax(0, qMin((int)frames.size()-1, index)); }
    char getLabel() const { return getLabel(index); }
    char getLabel(int index) const { return labels[index]; }
    void setLabel(char label) { labels[index] = label; }

    Leap::Frame getFrame() const {return frames[index];}
    QImage getImage() const;

    int save();

private:
    SequenceMarker();
    int load(QString);

    std::string fileName;
    std::vector<Leap::Frame> frames;
    std::vector<QImage> IRimages;
    std::vector<char> labels;
    int index = 0;
};

#endif // SEQUENCEMARKER_H
