TEMPLATE = lib
#CONFIG += console #coment it
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    phedfastcgihandler.cpp \
    photo.cpp \
    databasemanager.cpp \
    jsonFormatter.cpp

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    phedfastcgihandler.h \
    photo.h \
    databasemanager.h \
    jsonFormatter.h


CONFIG(release, debug|release): LIBS += -lfastcgi-daemon2 -pthread -lmongoclient -lboost_thread-mt -lboost_filesystem -lboost_system -lglog
CONFIG(debug, debug|release): LIBS += -lfastcgi-daemon2 -pthread -lmongoclient -lboost_thread-mt -lboost_filesystem -lboost_system -lglog


