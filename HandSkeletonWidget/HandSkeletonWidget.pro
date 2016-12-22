
QT       += opengl
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L/home/adeykin/projects/leapmotionSDK/LeapSDK/lib/x64 -lLeap
INCLUDEPATH += /home/adeykin/projects/leapmotionSDK/LeapSDK/include

TARGET = HandSkeletonWidget
TEMPLATE = lib
#CONFIG = staticlib
CONFIG += c++11 (Qt5)

SOURCES += handskeletonwidget.cpp
HEADERS  += handskeletonwidget.h
