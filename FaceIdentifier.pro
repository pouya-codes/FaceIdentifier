#-------------------------------------------------
#
# Project created by QtCreator 2017-02-01T16:34:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FaceIdentifier
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    Classifier.cpp \
    GetSampels.cpp \
    PoseEstimator.cpp \
    TrainClassifier.cpp \
    sampleadder.cpp \
    FeatureExtractorVGG.cpp


HEADERS  += mainwindow.h \
    Classifier.h \
    GetSampels.h \
    PoseEstimator.h \
    TrainClassifier.h \
    sampleadder.h \
    FeatureExtractorVGG.h \
# Graph_User_Nodes.h \
    SystemSetting.h

FORMS    += mainwindow.ui \
    sampleadder.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
unix: PKGCONFIG += zbar
#unix: PKGCONFIG += visionworks
#unix: PKGCONFIG += nvxio

LIBS += -lcaffe \
        -lglog \
        -lprotobuf \
        -lpthread \
        -lboost_system \
        -ljpeg \
        -lpng \
        -lopenblas \
        -ldlib \
        -lpng12 \
        -llapack \
        -lboost_filesystem



