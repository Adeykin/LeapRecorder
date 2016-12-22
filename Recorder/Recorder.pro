LeapRecorder.pro


QT       += opengl
QT       += core gui


LIBS += -L/home/adeykin/projects/leapmotionSDK/LeapSDK/lib/x64 -lLeap
INCLUDEPATH += /home/adeykin/projects/leapmotionSDK/LeapSDK/include

TARGET = LeapRecorder
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    samplelistiner.cpp \
    handskeletonwidget.cpp \
    recorder.cpp

HEADERS  += mainwindow.h \
    samplelistiner.h \
    handskeletonwidget.h \
    recorder.h


CONFIG   += c++11 (Qt5)
