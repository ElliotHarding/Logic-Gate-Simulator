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
        main.cpp \
        mainwindow.cpp \
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
        gatefieldscontainer.cpp \

HEADERS += \
        mainwindow.h \
        clickmode.h \
        gatereader.h \
        AllGates.h \
        filelocations.h \
        gatefield.h \
        gatefieldscontainer.h \
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

FORMS += \
        mainwindow.ui \
        Dialogs/dlg_gateinfo.ui \
        Dialogs/dlg_home.ui \
        Dialogs/dlg_savegatecollection.ui \
        Dialogs/dlg_userinput.ui \
        Dialogs/widget_advanced.ui \
        Dialogs/widget_allgates.ui \
        Dialogs/widget_customgates.ui \
        Dialogs/widget_inputgates.ui \
        Dialogs/widget_standard.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \

RESOURCES += \
    resouces.qrc
