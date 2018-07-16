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

QImage SequenceMarker::getImage() const
{
    if( IRimages.size() > index )
        return IRimages[index];
    return QImage();
}

int SequenceMarker::load(QString fileName)
{
    Leap::Controller controller; //instance must be created

    this->fileName = fileName.toStdString();

    const int bufSize = 10000;
    char buf[bufSize];
    uint8_t version = 0;
    std::ifstream file(fileName.toStdString().c_str(), std::ios::binary);
    file.read(buf, 2); //Read magic sequense and version
    bool isMagicSequenceOk = buf[0] == 'M' && buf[1] == 'N';
    if(isMagicSequenceOk)
        version = file.get();
    else
    {
        qDebug() << "WARNING: Wrong magic sequence in file\n";
        file.seekg(0, file.beg);
    }

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

        //Read IR images
        if(version == 1)
        {
            QImage image(640, 240, QImage::Format::Format_Grayscale8);
            file.read((char*)image.bits(), 640*240);
            IRimages.push_back(std::move(image));
        }
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

