#-------------------------------------------------
#
# Project created by QtCreator 2016-10-04T22:56:49
#
#-------------------------------------------------

QT       += opengl
QT       += core gui

LIBS += -L/home/adeykin/projects/leapmotionSDK/LeapSDK/lib/x64 -lLeap
INCLUDEPATH += /home/adeykin/projects/leapmotionSDK/LeapSDK/include

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = subdirs
SUBDIRS = Recorder
#app1.depends = common
#app2.depends = common
#app3.depends = common

CONFIG   += c++11 (Qt5)
