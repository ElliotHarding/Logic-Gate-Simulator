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

SOURCES +=  \
    Tests.cpp

HEADERS += \
    Tests.h
