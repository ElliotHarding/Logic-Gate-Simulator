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
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gameobject.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gateand.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatecollection.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gateconstantactive.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/GateConstantInactive.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatenand.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatenor.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatenot.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatenumberoutput.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gateor.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gateeor.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/GateReciever.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/GateSingleOutput.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/GateTimer.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/GateToggle.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatexor.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatetriand.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatetrieor.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatetrior.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatefield.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/dlg_home.o"
LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/*.o"

DISTFILES += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/"

SOURCES +=  \
    Tests.cpp

HEADERS += \
    Tests.h
