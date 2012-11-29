#-------------------------------------------------
#
# Project created by QtCreator 2012-07-17T19:34:42
#
#-------------------------------------------------

QT       += core gui

TARGET = NeuralNetwork
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    NeuralNetwork.cpp

HEADERS  += MainWindow.h \
    NeuralNetwork.h

FORMS    += MainWindow.ui

mac {

# OpenMP
QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

# OpenCV
INCLUDEPATH += /usr/local/Cellar/opencv/2.4.2/include/opencv2
INCLUDEPATH += /usr/local/Cellar/opencv/2.4.2/include
LIBS += -L/usr/local/lib \
  -lopencv_gpu \
  -lopencv_video \
  -lopencv_objdetect \
  -lopencv_ml \
  -lopencv_legacy \
  -lopencv_imgproc \
  -lopencv_highgui \
  -lopencv_contrib \
  -lopencv_flann \
  -lopencv_features2d \
  -lopencv_core
}

unix {

# OpenCV
INCLUDEPATH += /usr/local/include/opencv2
LIBS += -L/usr/local/lib \
  -lopencv_calib3d \
  -lopencv_contrib \
  -lopencv_core \
  -lopencv_features2d \
  -lopencv_flann \
  -lopencv_gpu \
  -lopencv_highgui \
  -lopencv_imgproc \
  -lopencv_legacy \
  -lopencv_ml \
  -lopencv_nonfree \
  -lopencv_objdetect \
  -lopencv_photo \
  -lopencv_stitching \
  -lopencv_ts \
  -lopencv_video \
  -lopencv_videostab
}
