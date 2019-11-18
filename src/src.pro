QT += widgets
CONFIG += c++17

TARGET = src
TEMPLATE = app

include(../minefield-src.pri)

SOURCES += main.cpp

#QMAKE_CXXFLAGS += -Weffc++
#QMAKE_CXXFLAGS += -isystem
