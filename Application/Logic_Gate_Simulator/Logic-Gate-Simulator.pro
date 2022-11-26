#-------------------------------------------------
#
# Project created by QtCreator 2019-03-31T00:48:54
#
#-------------------------------------------------

QT       += core gui script xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Logic-Gate-Simulator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += resources_big

INCLUDEPATH += \
    Dialogs \
    GameObjects

SOURCES += \
    Dialogs/dlg_booleanexpressions.cpp \
    Dialogs/dlg_conversionconfig.cpp \
    Dialogs/dlg_editscript.cpp \
    Dialogs/dlg_message.cpp \
    Dialogs/dlg_task.cpp \
    Dialogs/dlg_textedit.cpp \
    Dialogs/dlg_truthtable.cpp \
    Dialogs/dlg_truthtablecreate.cpp \
    Dialogs/widget_helperpopup.cpp \
    Dialogs/widget_spawnedgate.cpp \
    GameObjects/gateeor.cpp \
    GameObjects/gatefpga.cpp \
    GameObjects/gatenand.cpp \
    GameObjects/gatenor.cpp \
    GameObjects/gatetrieor.cpp \
    GameObjects/gatexor.cpp \
    GameObjects/textlabel.cpp \
    booleanexpression.cpp \
    circuit.cpp \
    converter.cpp \
    customsettings.cpp \
    logger.cpp \
    main.cpp \
    gatefield.cpp \
    gatereader.cpp \
    Dialogs/dlg_home.cpp \
    Dialogs/dlg_gateinfo.cpp \
    Dialogs/dlg_savegatecollection.cpp \
    Dialogs/simpleslider.cpp \
    Dialogs/widget_advanced.cpp \
    Dialogs/widget_allgates.cpp \
    Dialogs/widget_customgates.cpp \
    Dialogs/widget_inputgates.cpp \
    Dialogs/widget_standard.cpp \
    GameObjects/gameobject.cpp \
    GameObjects/gate.cpp \
    GameObjects/gateand.cpp \
    GameObjects/gatecollection.cpp \
    GameObjects/gateconstantactive.cpp \
    GameObjects/GateConstantInactive.cpp \
    GameObjects/gatenot.cpp \
    GameObjects/gateor.cpp \
    GameObjects/GateReciever.cpp \
    GameObjects/GateSingleOutput.cpp \
    GameObjects/GateTimer.cpp \
    GameObjects/GateToggle.cpp \
    Dialogs/dlg_load.cpp \
    GameObjects/gatetriand.cpp \
    Dialogs/movingwidget.cpp \
    GameObjects/gatetrior.cpp \
    GameObjects/gatenumberoutput.cpp \
    truthtable.cpp \
    truthtabletobooleanexpressionthread.cpp

HEADERS += \
    Dialogs/dlg_booleanexpressions.h \
    Dialogs/dlg_conversionconfig.h \
    Dialogs/dlg_editscript.h \
    Dialogs/dlg_message.h \
    Dialogs/dlg_textedit.h \
    Dialogs/dlg_truthtable.h \
    Dialogs/dlg_truthtablecreate.h \
    Dialogs/widget_helperpopup.h \
    Dialogs/widget_spawnedgate.h \
    GameObjects/gateeor.h \
    GameObjects/gatefpga.h \
    GameObjects/gatenand.h \
    GameObjects/gatenor.h \
    GameObjects/gatetrieor.h \
    GameObjects/gatetypes.h \
    GameObjects/gatexor.h \
    GameObjects/textlabel.h \
    booleanexpression.h \
    circuit.h \
    clickmode.h \
    converter.h \
    customsettings.h \
    gatereader.h \
    AllGates.h \
    gatefield.h \
    Dialogs/dlg_gateinfo.h \
    Dialogs/dlg_home.h \
    Dialogs/dlg_savegatecollection.h \
    Dialogs/simpleslider.h \
    Dialogs/widget_advanced.h \
    Dialogs/widget_allgates.h \
    Dialogs/widget_customgates.h \
    Dialogs/widget_inputgates.h \
    Dialogs/widget_standard.h \
    GameObjects/gameobject.h \
    GameObjects/gate.h \
    GameObjects/gateand.h \
    GameObjects/gatecollection.h \
    GameObjects/GateConstantActive.h \
    GameObjects/GateConstantInactive.h \
    GameObjects/gatenot.h \
    GameObjects/gateor.h \
    GameObjects/GateReciever.h \
    GameObjects/GateSingleOutput.h \
    GameObjects/GateTimer.h \
    GameObjects/GateToggle.h \
    Dialogs/dlg_load.h \
    GameObjects/gatetriand.h \
    Dialogs/movingwidget.h \
    GameObjects/gatetrior.h \
    GameObjects/gatenumberoutput.h \
    logger.h \
    truthtable.h \
    truthtabletobooleanexpressionthread.h

FORMS += \
    Dialogs/dlg_booleanexpressions.ui \
    Dialogs/dlg_conversionconfig.ui \
    Dialogs/dlg_editscript.ui \
    Dialogs/dlg_message.ui \
    Dialogs/dlg_gateinfo.ui \
    Dialogs/dlg_home.ui \
    Dialogs/dlg_savegatecollection.ui \
    Dialogs/dlg_textedit.ui \
    Dialogs/dlg_truthtable.ui \
    Dialogs/dlg_truthtablecreate.ui \
    Dialogs/widget_advanced.ui \
    Dialogs/widget_allgates.ui \
    Dialogs/widget_customgates.ui \
    Dialogs/widget_helperpopup.ui \
    Dialogs/widget_inputgates.ui \
    Dialogs/widget_standard.ui \
    Dialogs/dlg_load.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resouces.qrc
