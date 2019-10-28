QT += widgets
QT += testlib
QT += gui
CONFIG += c++17 console

TEMPLATE = app

include (../minefield-src.pri)

APP_PATH = ../src
INCLUDEPATH += $$APP_PATH
DEPENDPATH += $$APP_PATH

HEADERS += \
    testcell.h 

SOURCES += \
    testcell.cpp 
