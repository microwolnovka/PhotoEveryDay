TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    dbengine.cpp \
    requesthandler.cpp

QMAKE_CXXFLAGS += -std=c++0x

OTHER_FILES += \
    fsgiPhotoEveryDay.conf

HEADERS += \
    dbengine.h \
    requesthandler.h

