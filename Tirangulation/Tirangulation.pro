#-------------------------------------------------
#
# Project created by QtCreator 2017-02-20T18:24:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tirangulation
TEMPLATE = app

SOURCES += main.cpp\
    widget.cpp \
    graphicsscene.cpp \

HEADERS  += widget.h \
    graphicsscene.h \

FORMS    += widget.ui

CONFIG(release, debug|release): LIBS += -L$$PWD/../build-TrisngulationLib-Desktop_Qt_5_8_0_MinGW_32bit-Release/release/ -ltrisngulationlib
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-TrisngulationLib-Desktop_Qt_5_8_0_MinGW_32bit-Debug/debug/ -ltrisngulationlib

INCLUDEPATH += $$PWD/../trisngulationlib
DEPENDPATH += $$PWD/../trisngulationlib
