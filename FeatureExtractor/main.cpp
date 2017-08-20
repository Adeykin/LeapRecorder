#include <Leap.h>

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>

struct LabeledFrame
{
    LabeledFrame() {}
    LabeledFrame(const Leap::Frame& _frame, char _label) : frame(_frame), label(_label) {}

    Leap::Frame frame;
    char label = 0;
};

std::vector<LabeledFrame> loadData(std::string inputFileGst, std::string inputFileLables)
{
    std::vector<LabeledFrame> labeledFrames;

    const int bufSize = 10000;
    char buf[bufSize];
    std::ifstream framesFile(inputFileGst.c_str(), std::ios::binary);
    std::ifstream labelsFile(inputFileLables, std::ios::binary);
    if( !labelsFile ) //labels file exists
    {
        std::cout << "Labels were not found";
        return std::vector<LabeledFrame>();
    }
    do
    {
        //Read Frame
        int32_t size;
        framesFile.read((char*)&size, 4);
        if(size > bufSize)
        {
            std::cout << "Size error " << size;
            return std::vector<LabeledFrame>();
        }
        std::string str(size, 0);
        framesFile.read((char*)str.data(), size);
        Leap::Frame reconstructedFrame;

        reconstructedFrame.deserialize(str);

        /*std::cout << "Frame id: " << reconstructedFrame.id()
                  << ", timestamp: " << reconstructedFrame.timestamp()
                  << ", hands: " << reconstructedFrame.hands().count()
                  << ", extended fingers: " << reconstructedFrame.fingers().extended().count()
                  << ", tools: " << reconstructedFrame.tools().count()
                  << ", gestures: " << reconstructedFrame.gestures().count() << std::endl;*/

        //Read label
        if(!labelsFile)
        {
            std::cout << "Wrong size of labels file\n";
            return std::vector<LabeledFrame>();
        }
        char label;
        labelsFile.get(label);

        //Construct element
        labeledFrames.emplace_back(reconstructedFrame, label);
    } while( framesFile );

    return labeledFrames;
}

std::vector<float> extractFeatures(const Leap::Frame& frame)
{
    std::vector<float> data;

    for(const auto& hand: frame.hands())
    {
        if(hand.isLeft())
            continue;

        const Leap::Arm& arm = hand.arm();
        data.push_back(hand.direction().yaw());
        data.push_back(hand.direction().roll());
        data.push_back(hand.direction().pitch());

        for(const auto finger: hand.fingers())
        {
            for (int i = 0; i < 4; i++)
            {
                const Leap::Bone& bone = finger.bone(static_cast<Leap::Bone::Type>(i));

                float pitch = bone.direction().pitch() - hand.direction().pitch();
                float yaw = bone.direction().yaw() - hand.direction().yaw();
                data.push_back(pitch);
                data.push_back(yaw);
            }
        }
    }

    return data;
}

int main(int argc, char *argv[])
{
    Leap::Controller controller; //instance must be created

    if( argc != 3 )
    {
        std::cout << "USAGE: ./FeatureExtractor <input.gst> <output.csv>\n";
        return -1;
    }

    std::string inputFileGst = argv[1];
    std::string inputFileLabels = inputFileGst + ".lbl";
    std::string outputFile = argv[2];

    std::ofstream output(outputFile);

    //Reading labels
    std::vector<LabeledFrame> inputFrames = loadData(inputFileGst, inputFileLabels);
    if(inputFrames.size() == 0)
    {
        std::cout << "Cant read frames\n";
        return -1;
    }

    //Feature extraction and normalization
    for(const auto& labeledFrame: inputFrames)
    {
        if(labeledFrame.label == 0) //dont analize unlabeled frames
            continue;
        std::vector<float> features = extractFeatures(labeledFrame.frame);
        if(features.size() == 0)
            continue;
        //output label
        output << (int)labeledFrame.label << ';';
        //output features
        std::copy(features.begin(), features.end()-1, std::ostream_iterator<float>(output,";"));
        output << features.back();
        output << '\n';
    }

    return 0;
}

