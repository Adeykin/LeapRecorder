QT += core
QT -= gui

LIBS += -L/home/adeykin/projects/leapmotionSDK/LeapSDK/lib/x64 -lLeap
INCLUDEPATH += /home/adeykin/projects/leapmotionSDK/LeapSDK/include

TARGET = FeatureExtractor
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

CONFIG   += c++11 (Qt5)

