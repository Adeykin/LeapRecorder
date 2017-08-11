#include "sequencemarker.h"
#include <fstream>
#include <string>
#include <memory>
#include <QDebug>

SequenceMarker *SequenceMarker::createSequenceMaerker(QString fileName)
{
    std::unique_ptr<SequenceMarker> seqMarker( new SequenceMarker );
    if(seqMarker->load(fileName) != 0)
        return nullptr;

    return seqMarker.release();
}

int SequenceMarker::save()
{
    std::string labelsFileName = fileName + ".lbl";
    std::ofstream labelsFile(labelsFileName, std::ios::binary);
    labelsFile.write(labels.data(), labels.size());
}

SequenceMarker::SequenceMarker()
{

}

int SequenceMarker::load(QString fileName)
{
    Leap::Controller controller; //instance must be created

    this->fileName = fileName.toStdString();

    const int bufSize = 10000;
    char buf[bufSize];
    std::ifstream file(fileName.toStdString().c_str(), std::ios::binary);
    do
    {
        int32_t size;
        file.read((char*)&size, 4);
        if(size > bufSize)
        {
            qDebug() << "Size error " << size;
            return -1;
        }
        std::string str(size, 0);
        qDebug() << "Read of size " << size;
        file.read((char*)str.data(), size);
        //buf[size] = '\0';
        Leap::Frame reconstructedFrame;

        qDebug() << "string size " << str.size();
        reconstructedFrame.deserialize(str);

        std::cout << "Frame id: " << reconstructedFrame.id()
                  << ", timestamp: " << reconstructedFrame.timestamp()
                  << ", hands: " << reconstructedFrame.hands().count()
                  << ", extended fingers: " << reconstructedFrame.fingers().extended().count()
                  << ", tools: " << reconstructedFrame.tools().count()
                  << ", gestures: " << reconstructedFrame.gestures().count() << std::endl;

        frames.push_back(reconstructedFrame);
    } while( file );

    std::string labelsFileName = fileName.toStdString() + ".lbl";
    std::ifstream labelsFile(labelsFileName, std::ios::binary);
    if( labelsFile ) //labels file exists
    {
        std::copy(std::istream_iterator<char>(labelsFile), std::istream_iterator<char>(), std::back_inserter(labels));
    }
    else
    {
        labels.resize(frames.size(), 0);
    }

    qDebug() << "Reading finished; Frames " << frames.size();
    return 0; // ERR_OK
}

