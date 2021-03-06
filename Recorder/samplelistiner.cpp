#include "samplelistiner.h"
#include <iostream>

using namespace Leap;

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};


SampleListiner::SampleListiner()
{}

void SampleListiner::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListiner::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListiner::onDisconnect(const Controller& controller) {
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void SampleListiner::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListiner::onFrame(const Controller& controller) {
  const Frame frame = controller.frame();

  /*if(widget)
      widget->setFrame(frame);

  if(recorder)
      recorder->setFrame(frame);

  if(lableImage) {
      std::cout  << "DRAW\n";

      Leap::Image frameImage = frame.images()[0];

      //cameraLabel->setPixmap(*pixmap);
      QImage image(frameImage.data(), frameImage.width(), frameImage.height(), QImage::Format::Format_Grayscale8);


      //image.scaled(100,100);
      QPixmap pixmap = QPixmap::fromImage(image);
      //pixmap.scaled(640, 480);
      lableImage->setPixmap(pixmap);
  }*/

  for(IFrameHanler* handler: frameHandlers) {
      handler->setFrame(frame);
  }

}

void SampleListiner::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void SampleListiner::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

void SampleListiner::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

void SampleListiner::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void SampleListiner::onServiceDisconnect(const Controller& controller) {
    std::cout << "Service Disconnected" << std::endl;
}

void SampleListiner::addFrameHandler(IFrameHanler *framehandler){
    frameHandlers.push_back(framehandler);
}

