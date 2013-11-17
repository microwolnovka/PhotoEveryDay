TEMPLATE = app #lib
CONFIG += console #coment it
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    phedfastcgihandler.cpp \
    photo.cpp \
    databasemanager.cpp

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += \
    phedfastcgihandler.h \
    photo.h \
    databasemanager.h


CONFIG(release, debug|release): LIBS += -lfastcgi-daemon2 -pthread -lmongoclient -lboost_thread-mt -lboost_filesystem -lboost_system
CONFIG(debug, debug|release): LIBS += -lfastcgi-daemon2 -pthread -lmongoclient -lboost_thread-mt -lboost_filesystem -lboost_system


