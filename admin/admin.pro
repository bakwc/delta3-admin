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
        mainwindow.cpp \
    network.cpp \
    client.cpp \
    telnetform.cpp \
    netextract.cpp \
    fileform.cpp \
    graphform.cpp \
    clientinfodialog.cpp

HEADERS  += mainwindow.h \
    network.h \
    client.h \
    telnetform.h \
    defines.h \
    utils.h \
    netextract.h \
    fileform.h \
    graphform.h \
    clientinfodialog.h

FORMS    += mainwindow.ui \
    telnetform.ui \
    fileform.ui \
    graphform.ui \
    clientinfodialog.ui
