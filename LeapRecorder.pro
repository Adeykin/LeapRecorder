#-------------------------------------------------
#
# Project created by QtCreator 2016-10-04T22:56:49
#
#-------------------------------------------------

TEMPLATE = subdirs
SUBDIRS = HandSkeletonWidget Recorder  Marker \
    FeatureExtractor
Recorder.depends = HandSkeletonWidget
Marker.depends = HandSkeletonWidget
