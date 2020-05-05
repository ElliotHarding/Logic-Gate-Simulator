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

SOURCES += \
    ../../Dialogs/dlg_circuittaskdesigner.cpp \
    ../../Dialogs/dlg_circuittaskdesignersetup.cpp \
    ../../Dialogs/dlg_message.cpp \
    ../../Dialogs/dlg_task.cpp \
    ../../Dialogs/dlg_taskmanager.cpp \
    ../../Dialogs/dlg_textedit.cpp \
    ../../Dialogs/dlg_truthtabletaskdesigner.cpp \
    ../../Dialogs/widget_text.cpp \
    ../../Dialogs/widget_truthtable.cpp \
    ../../GameObjects/gateeor.cpp \
    ../../GameObjects/gatefpga.cpp \
    ../../GameObjects/gatenand.cpp \
    ../../GameObjects/gatenor.cpp \
    ../../GameObjects/gatetrieor.cpp \
    ../../GameObjects/gatexor.cpp \
    ../../GameObjects/textlabel.cpp \
    ../../circuitoptimizer.cpp \
    ../../gatefield.cpp \
    ../../gatereader.cpp \
    ../../Dialogs/dlg_gateinfo.cpp \
    ../../Dialogs/dlg_home.cpp \
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
    ../../truthtables.cpp

HEADERS += \
    ../../Dialogs/dlg_circuittaskdesigner.h \
    ../../Dialogs/dlg_circuittaskdesignersetup.h \
    ../../Dialogs/dlg_message.h \
    ../../Dialogs/dlg_task.h \
    ../../Dialogs/dlg_taskmanager.h \
    ../../Dialogs/dlg_textedit.h \
    ../../Dialogs/dlg_truthtabletaskdesigner.h \
    ../../Dialogs/widget_text.h \
    ../../Dialogs/widget_truthtable.h \
    ../../GameObjects/gateeor.h \
    ../../GameObjects/gatefpga.h \
    ../../GameObjects/gatenand.h \
    ../../GameObjects/gatenor.h \
    ../../GameObjects/gatetrieor.h \
    ../../GameObjects/gatetypes.h \
    ../../GameObjects/gatexor.h \
    ../../GameObjects/textlabel.h \
    ../../circuitoptimizer.h \
    ../../clickmode.h \
    ../../gatereader.h \
    ../../AllGates.h \
    ../../filelocations.h \
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
    ../../truthtables.h

FORMS += \
    ../../Dialogs/dlg_circuittaskdesigner.ui \
    ../../Dialogs/dlg_circuittaskdesignersetup.ui \
    ../../Dialogs/dlg_message.ui \
    ../../Dialogs/dlg_gateinfo.ui \
    ../../Dialogs/dlg_home.ui \
    ../../Dialogs/dlg_savegatecollection.ui \
    ../../Dialogs/dlg_taskmanager.ui \
    ../../Dialogs/dlg_textedit.ui \
    ../../Dialogs/widget_advanced.ui \
    ../../Dialogs/widget_allgates.ui \
    ../../Dialogs/widget_customgates.ui \
    ../../Dialogs/widget_inputgates.ui \
    ../../Dialogs/widget_standard.ui \
    ../../Dialogs/dlg_load.ui \
    ../../Dialogs/widget_text.ui \
    ../../Dialogs/widget_truthtable.ui

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

DISTFILES += "../../../build-Logic-Gate-Simulator-Desktop_Qt_5_14_2_MinGW_32_bit-Debug/debug/"

SOURCES +=  \
    Tests.cpp

HEADERS += \
    Tests.h