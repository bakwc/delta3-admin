#-------------------------------------------------
#
# Project created by QtCreator 2012-07-10T11:36:26
#
#-------------------------------------------------

QT += core network gui
TARGET = delta3admin
TEMPLATE = lib
DESTDIR = ..

QMAKE_CXXFLAGS += -std=c++0x

win32 {
   # To compile DLL library use the following definition:
   CONFIG += DLL
   DEFINES += DELTA3_ADMIN_LIBRARY
   # To compile static library use following definitions
   # CONFIG += staticlib
}

SOURCES += network.cpp \
    client.cpp \
    netextract.cpp \
    Protocols/abstrproto.cpp \
    Protocols/telnet.cpp \
    Protocols/graphics.cpp \
    Protocols/file.cpp \
    Protocols/proxy.cpp


HEADERS  += network.h \
    client.h \
    defines.h \
    utils.h \
    netextract.h \
    Protocols/abstrproto.h \
    Protocols/telnet.h \
    Protocols/graphics.h \
    Protocols/file.h \
    Protocols/proxy.h
