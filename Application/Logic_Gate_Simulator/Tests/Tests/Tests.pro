QT += testlib
QT += widgets
#QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += "../../"
INCLUDEPATH += "../../Dialogs"
INCLUDEPATH += "../../GameObjects"

LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gate.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gateand.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gameobject.o"

DISTFILES += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/"

SOURCES +=  \
    Tests.cpp

HEADERS += \
    Tests.h
