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

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        gate.cpp \
        gateand.cpp \
        gatenot.cpp \
        gateor.cpp \
        gatefield.cpp \
        dlg_home.cpp \
        gameobject.cpp \
        simpleslider.cpp \
        gatecollection.cpp \
        dlg_savegatecollection.cpp \
        GateToggle.cpp \
        GateReciever.cpp \
        GateConstantInactive.cpp \
        GateSingleOutput.cpp \
        GateConstantActive.cpp \
        GateTimer.cpp \
        dlg_gateinfo.cpp \
        widget_allgates.cpp \
        widget_advanced.cpp \
        widget_standard.cpp \
        widget_customgates.cpp \
        widget_inputgates.cpp

HEADERS += \
        mainwindow.h \
        gateand.h \
        clickmode.h \
        dlg_home.h \
        gameobject.h \
        gate.h \
        gateand.h \
        gatefield.h \
        gatenot.h \
        gateor.h \
        simpleslider.h \
        gatereader.h \
        gatecollection.h \
        dlg_savegatecollection.h \
        GateToggle.h \
        GateReciever.h \
        GateConstantInactive.h \
        GateSingleOutput.h \
        GateConstantActive.h \
        GateTimer.h \
        AllGates.h \
        dlg_gateinfo.h \
        widget_allgates.h \
        widget_advanced.h \
        widget_standard.h \
        widget_customgates.h \
        widget_inputgates.h

FORMS += \
        mainwindow.ui \
        dlg_home.ui \
        dlg_savegatecollection.ui \
        dlg_userinput.ui \
        dlg_gateinfo.ui \
        widget_allgates.ui \
        widget_advanced.ui \
        widget_standard.ui \
        widget_customgates.ui \
        widget_inputgates.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \

RESOURCES += \
    resouces.qrc
