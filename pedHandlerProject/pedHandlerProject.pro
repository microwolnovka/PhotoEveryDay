TEMPLATE = lib #app
#CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    phedfastcgihandler.cpp

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    phedfastcgihandler.h


CONFIG(release, debug|release): LIBS += -lfastcgi-daemon2
CONFIG(debug, debug|release): LIBS += -lfastcgi-daemon2

