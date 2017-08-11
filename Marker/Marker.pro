Marker.pro

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L/home/adeykin/projects/leapmotionSDK/LeapSDK/lib/x64 -lLeap
LIBS += -L../HandSkeletonWidget -lHandSkeletonWidget
INCLUDEPATH += /home/adeykin/projects/leapmotionSDK/LeapSDK/include
INCLUDEPATH += ../HandSkeletonWidget

TARGET = Marker
TEMPLATE = app

SOURCES += main.cpp\
    mainwindowmarker.cpp \
    sequencemarker.cpp

HEADERS  += \
    mainwindowmarker.h \
    sequencemarker.h

CONFIG   += c++11 (Qt5)

FORMS += \
    mainwindow.ui
