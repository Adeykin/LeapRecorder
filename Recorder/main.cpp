#include "mainwindow.h"
#include <QApplication>
#include "samplelistiner.h"
#include <Leap.h>

#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    /*Leap::Controller controller1;
    std::ifstream file("/home/adeykin/1.gst", std::ios::binary);
    int32_t size;
    file.read((char*)&size, 4);
    std::cout << "read size: " << size << '\n';
    char buf[size];
    file.read((char*)buf, size);
    Leap::Frame reconstructedFrame;
    reconstructedFrame.deserialize((unsigned char*)buf, size);

    std::cout << "rframe: " << reconstructedFrame.isValid() << ' ' << reconstructedFrame.id() << ' ' << reconstructedFrame.fingers().extended().count() << '\n';

    return 0;
*/
    QApplication a(argc, argv);
    MainWindow w;

    // Create a sample listener and controller
    //SampleListener listener;
    SampleListiner listener;
    listener.addFrameHandler(w.getHandSkeletonWidget());
    listener.addFrameHandler(w.getRecorder());
    listener.addFrameHandler(w.getVideoWidget());
    Leap::Controller controller;

    controller.setPolicy(Leap::Controller::POLICY_IMAGES);

    // Have the sample listener receive events from the controller
    controller.addListener(listener);

    //if (argc > 1 && strcmp(argv[1], "--bg") == 0)
    //controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

    // Keep this process running until Enter is pressed
    //std::cout << "Press Enter to quit..." << std::endl;
    //std::cin.get();

    // Remove the sample listener when done
    //controller.removeListener(listener);


    w.show();

    return a.exec();
}
