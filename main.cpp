#include "mainwindow.h"
#include <QApplication>
#include "samplelistiner.h"
#include <Leap.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Create a sample listener and controller
    //SampleListener listener;
    SampleListiner listener( w.getHandSkeletonWidget() );
    Leap::Controller controller;

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
