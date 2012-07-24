#-------------------------------------------------
#
# Project created by QtCreator 2012-07-10T11:36:26
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = admin
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x


SOURCES += main.cpp\
	UI/mainwindow.cpp \
    network.cpp \
    client.cpp \
    UI/telnetform.cpp \
    netextract.cpp \
    UI/fileform.cpp \
    UI/graphform.cpp \
    UI/clientinfodialog.cpp \
    Protocols/abstrproto.cpp \
    Protocols/telnet.cpp

HEADERS  += UI/mainwindow.h \
    network.h \
    client.h \
    UI/telnetform.h \
    defines.h \
    utils.h \
    netextract.h \
    UI/fileform.h \
    UI/graphform.h \
    UI/clientinfodialog.h \
    Protocols/abstrproto.h \
    Protocols/telnet.h

FORMS    += UI/mainwindow.ui \
    UI/telnetform.ui \
    UI/fileform.ui \
    UI/graphform.ui \
    UI/clientinfodialog.ui
