QT += testlib
QT += core xml script gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#QT -= gui

#QMAKE_CXXFLAGS_DEBUG *= -O

CONFIG += qt console warn_on depend_includepath testcase
CONFIG += resources_big
CONFIG += c++11
#CONFIG -= app_bundle
#CONFIG += debug
#QMAKE_CXXFLAGS += -O0 -g -ggdb

#QMAKE_CXXFLAGS_DEBUG -= -O1
#QMAKE_CXXFLAGS_DEBUG -= -O2
#QMAKE_CXXFLAGS_DEBUG -= -O3
#QMAKE_CXXFLAGS_DEBUG *= -O
#
#QMAKE_CXXFLAGS_RELEASE -= -O1
#QMAKE_CXXFLAGS_RELEASE -= -O2
#QMAKE_CXXFLAGS_RELEASE -= -O3
#QMAKE_CXXFLAGS_RELEASE *= -O

TEMPLATE = app

INCLUDEPATH += "../../"
INCLUDEPATH += "../../Dialogs"
INCLUDEPATH += "../../GameObjects"

SOURCES += \
    ../../Dialogs/dlg_booleanexpressions.cpp \
    ../../Dialogs/dlg_conversionconfig.cpp \
    ../../Dialogs/dlg_editscript.cpp \
    ../../Dialogs/dlg_message.cpp \
    ../../Dialogs/dlg_task.cpp \
    ../../Dialogs/dlg_textedit.cpp \
    ../../Dialogs/dlg_truthtable.cpp \
    ../../Dialogs/dlg_truthtablecreate.cpp \
    ../../Dialogs/widget_spawnedgate.cpp \
    ../../GameObjects/gateeor.cpp \
    ../../GameObjects/gatefpga.cpp \
    ../../GameObjects/gatenand.cpp \
    ../../GameObjects/gatenor.cpp \
    ../../GameObjects/gatetrieor.cpp \
    ../../GameObjects/gatexor.cpp \
    ../../GameObjects/textlabel.cpp \
    ../../booleanexpression.cpp \
    ../../circuit.cpp \
    ../../circuitfromtruthtablethread.cpp \
    ../../converter.cpp \
    ../../logger.cpp \
    ../../gatefield.cpp \
    ../../gatereader.cpp \
    ../../Dialogs/dlg_home.cpp \
    ../../Dialogs/dlg_gateinfo.cpp \
    ../../Dialogs/dlg_savegatecollection.cpp \
    ../../Dialogs/simpleslider.cpp \
    ../../Dialogs/widget_advanced.cpp \
    ../../Dialogs/widget_allgates.cpp \
    ../../Dialogs/widget_customgates.cpp \
    ../../Dialogs/widget_inputgates.cpp \
    ../../Dialogs/widget_standard.cpp \
    ../../GameObjects/gameobject.cpp \
    ../../GameObjects/gate.cpp \
    ../../GameObjects/gateand.cpp \
    ../../GameObjects/gatecollection.cpp \
    ../../GameObjects/gateconstantactive.cpp \
    ../../GameObjects/GateConstantInactive.cpp \
    ../../GameObjects/gatenot.cpp \
    ../../GameObjects/gateor.cpp \
    ../../GameObjects/GateReciever.cpp \
    ../../GameObjects/GateSingleOutput.cpp \
    ../../GameObjects/GateTimer.cpp \
    ../../GameObjects/GateToggle.cpp \
    ../../Dialogs/dlg_load.cpp \
    ../../GameObjects/gatetriand.cpp \
    ../../Dialogs/movingwidget.cpp \
    ../../GameObjects/gatetrior.cpp \
    ../../GameObjects/gatenumberoutput.cpp \
    ../../truthtable.cpp


HEADERS += \
    ../../Dialogs/dlg_booleanexpressions.h \
    ../../Dialogs/dlg_conversionconfig.h \
    ../../Dialogs/dlg_editscript.h \
    ../../Dialogs/dlg_message.h \
    ../../Dialogs/dlg_textedit.h \
    ../../Dialogs/dlg_truthtable.h \
    ../../Dialogs/dlg_truthtablecreate.h \
    ../../Dialogs/widget_spawnedgate.h \
    ../../GameObjects/gateeor.h \
    ../../GameObjects/gatefpga.h \
    ../../GameObjects/gatenand.h \
    ../../GameObjects/gatenor.h \
    ../../GameObjects/gatetrieor.h \
    ../../GameObjects/gatetypes.h \
    ../../GameObjects/gatexor.h \
    ../../GameObjects/textlabel.h \
    ../../booleanexpression.h \
    ../../circuit.h \
    ../../circuitfromtruthtablethread.h \
    ../../clickmode.h \
    ../../converter.h \
    ../../gatereader.h \
    ../../AllGates.h \
    ../../gatefield.h \
    ../../Dialogs/dlg_gateinfo.h \
    ../../Dialogs/dlg_home.h \
    ../../Dialogs/dlg_savegatecollection.h \
    ../../Dialogs/simpleslider.h \
    ../../Dialogs/widget_advanced.h \
    ../../Dialogs/widget_allgates.h \
    ../../Dialogs/widget_customgates.h \
    ../../Dialogs/widget_inputgates.h \
    ../../Dialogs/widget_standard.h \
    ../../GameObjects/gameobject.h \
    ../../GameObjects/gate.h \
    ../../GameObjects/gateand.h \
    ../../GameObjects/gatecollection.h \
    ../../GameObjects/GateConstantActive.h \
    ../../GameObjects/GateConstantInactive.h \
    ../../GameObjects/gatenot.h \
    ../../GameObjects/gateor.h \
    ../../GameObjects/GateReciever.h \
    ../../GameObjects/GateSingleOutput.h \
    ../../GameObjects/GateTimer.h \
    ../../GameObjects/GateToggle.h \
    ../../Dialogs/dlg_load.h \
    ../../GameObjects/gatetriand.h \
    ../../Dialogs/movingwidget.h \
    ../../GameObjects/gatetrior.h \
    ../../GameObjects/gatenumberoutput.h \
    ../../logger.h \
    ../../truthtable.h


FORMS += \
    ../../Dialogs/dlg_booleanexpressions.ui \
    ../../Dialogs/dlg_conversionconfig.ui \
    ../../Dialogs/dlg_editscript.ui \
    ../../Dialogs/dlg_message.ui \
    ../../Dialogs/dlg_gateinfo.ui \
    ../../Dialogs/dlg_home.ui \
    ../../Dialogs/dlg_savegatecollection.ui \
    ../../Dialogs/dlg_textedit.ui \
    ../../Dialogs/dlg_truthtable.ui \
    ../../Dialogs/dlg_truthtablecreate.ui \
    ../../Dialogs/widget_advanced.ui \
    ../../Dialogs/widget_allgates.ui \
    ../../Dialogs/widget_customgates.ui \
    ../../Dialogs/widget_inputgates.ui \
    ../../Dialogs/widget_standard.ui \
    ../../Dialogs/dlg_load.ui

#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gate.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gameobject.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gateand.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatecollection.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gateconstantactive.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/GateConstantInactive.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatenand.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatenor.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatenot.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatenumberoutput.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gateor.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gateeor.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/GateReciever.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/GateSingleOutput.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/GateTimer.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/GateToggle.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatexor.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatetriand.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatetrieor.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatetrior.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/gatefield.o"
#LIBS += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/dlg_home.o"

#DISTFILES += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/"

SOURCES +=  \
    Tests.cpp

HEADERS += \
    Tests.h
