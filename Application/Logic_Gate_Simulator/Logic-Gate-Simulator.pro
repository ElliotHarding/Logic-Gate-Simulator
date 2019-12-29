#-------------------------------------------------
#
# Project created by QtCreator 2019-03-31T00:48:54
#
#-------------------------------------------------

QT       += core gui

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

INCLUDEPATH += \
    Dialogs \
    GameObjects

SOURCES += \
    Dialogs/dlg_message.cpp \
    Dialogs/dlg_textedit.cpp \
    GameObjects/gateeor.cpp \
    GameObjects/gatefpga.cpp \
    GameObjects/gatenand.cpp \
    GameObjects/gatenor.cpp \
    GameObjects/gatetrieor.cpp \
    GameObjects/gatexor.cpp \
    GameObjects/textlabel.cpp \
    circuitoptimizer.cpp \
        main.cpp \
        gatefield.cpp \
        gatereader.cpp \
        Dialogs/dlg_gateinfo.cpp \
        Dialogs/dlg_home.cpp \
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
    GameObjects/gatenumberoutput.cpp

HEADERS += \
    Dialogs/dlg_message.h \
    Dialogs/dlg_textedit.h \
    GameObjects/gateeor.h \
    GameObjects/gatefpga.h \
    GameObjects/gatenand.h \
    GameObjects/gatenor.h \
    GameObjects/gatetrieor.h \
    GameObjects/gatetypes.h \
    GameObjects/gatexor.h \
    GameObjects/textlabel.h \
    circuitoptimizer.h \
        clickmode.h \
        gatereader.h \
        AllGates.h \
        filelocations.h \
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
    GameObjects/gatenumberoutput.h

FORMS += \
    Dialogs/dlg_message.ui \
        Dialogs/dlg_gateinfo.ui \
        Dialogs/dlg_home.ui \
        Dialogs/dlg_savegatecollection.ui \
    Dialogs/dlg_textedit.ui \
        Dialogs/widget_advanced.ui \
        Dialogs/widget_allgates.ui \
        Dialogs/widget_customgates.ui \
        Dialogs/widget_inputgates.ui \
        Dialogs/widget_standard.ui \
    Dialogs/dlg_load.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Resources/Button Icons/icon-bin.png \
    Resources/Button Icons/icon-drag.png \
    Resources/Button Icons/icon-file-down.png \
    Resources/Button Icons/icon-file-explorer.png \
    Resources/Button Icons/icon-file-up.png \
    Resources/Button Icons/icon-gate-and.png \
    Resources/Button Icons/icon-gate-collection.png \
    Resources/Button Icons/icon-gate-input.png \
    Resources/Button Icons/icon-gate-input-off.png \
    Resources/Button Icons/icon-gate-input-on.png \
    Resources/Button Icons/icon-gate-not.png \
    Resources/Button Icons/icon-gate-or.png \
    Resources/Button Icons/icon-gate-output.png \
    Resources/Button Icons/icon-gate-selection.png \
    Resources/Button Icons/icon-gate-timer.png \
    Resources/Button Icons/icon-link-basic.png \
    Resources/Button Icons/icon-link-delete.png \
    Resources/Button Icons/icon-new-page.png \
    Resources/Button Icons/icon-pan.png \
    Resources/Button Icons/icon-tool.png \
    Resources/Button Icons/icon-zoom-in.png \
    Resources/Button Icons/icon-zoom-out.png \
    Resources/Button Icons/icon-redo.png \
    Resources/Button Icons/icon-undo.png \
    Resources/Button Icons/icon-gate-tri-and.png \
    Resources/Button Icons/icon-gate-tri-or.png \
    Resources/Button Icons/icon-gate-tri-and.png \
    Resources/Button Icons/icon-gate-tri-or.png \
    Resources/Gates/gate-number-output.png \
    Resources/Gates/gate-tri-and.png

RESOURCES += \
    resouces.qrc
