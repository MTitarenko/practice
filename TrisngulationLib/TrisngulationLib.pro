#-------------------------------------------------
#
# Project created by QtCreator 2017-02-21T22:32:28
#
#-------------------------------------------------

QT       -= gui

TARGET = TrisngulationLib
TEMPLATE = lib
CONFIG  += c++11
DEFINES += TRISNGULATIONLIB_LIBRARY

SOURCES += trisngulationlib.cpp\
    triangle.cpp \
    quadtree.cpp

HEADERS += trisngulationlib.h\
    trisngulationlib_global.h\
    edge.h \
    point.h \
    triangle.h \
    quadtree.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
