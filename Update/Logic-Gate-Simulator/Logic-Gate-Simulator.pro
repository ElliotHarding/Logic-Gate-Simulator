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
    starterScreen.cpp \
    Simulator.cpp \
    memory.cpp \
    mainwindow.cpp \
    link.cpp \
    IOgates.cpp \
    Instructions.cpp \
    image.cpp \
    gateButton.cpp \
    gate.cpp \
    gameObjectFunctions.cpp \
    Button.cpp \
    attachers.cpp \
    allGates.cpp \
    allGateButtons.cpp \
    gate.cpp \
    gateand.cpp \
    gatenot.cpp \
    gateor.cpp

HEADERS += \
        mainwindow.h \
    allGateButtons.h \
    allGates.h \
    attachers.h \
    gameObjectFunctions.h \
    gate.h \
    gateButton.h \
    identifiers.h \
    image.h \
    Instructions.h \
    IOgates.h \
    link.h \
    location.h \
    mainwindow.h \
    memory.h \
    Simulator.h \
    starterScreen.h \
    gate.h \
    gateand.h \
    gatenot.h \
    gateor.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
