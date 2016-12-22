LeapRecorder.pro

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L/home/adeykin/projects/leapmotionSDK/LeapSDK/lib/x64 -lLeap
LIBS += -L../HandSkeletonWidget -lHandSkeletonWidget
INCLUDEPATH += /home/adeykin/projects/leapmotionSDK/LeapSDK/include
INCLUDEPATH += ../HandSkeletonWidget

TARGET = Recorder
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    samplelistiner.cpp \
    recorder.cpp

HEADERS  += mainwindow.h \
    samplelistiner.h \
    recorder.h

CONFIG   += c++11 (Qt5)
