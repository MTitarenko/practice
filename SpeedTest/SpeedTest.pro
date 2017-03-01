TEMPLATE = app
CONFIG += console c++11

SOURCES += main.cpp

CONFIG(release, debug|release): LIBS += -L$$PWD/../build-TrisngulationLib-Desktop_Qt_5_8_0_MinGW_32bit-Release/release/ -ltrisngulationlib
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-TrisngulationLib-Desktop_Qt_5_8_0_MinGW_32bit-Debug/debug/ -ltrisngulationlib

INCLUDEPATH += $$PWD/../trisngulationlib
DEPENDPATH += $$PWD/../trisngulationlib
