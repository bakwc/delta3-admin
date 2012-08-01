#-------------------------------------------------
#
# Project created by QtCreator 2012-07-10T11:36:26
#
#-------------------------------------------------


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += core gui network

TARGET = d3aDesktop
TEMPLATE = app
INCLUDEPATH += ../admin

unix {
    QMAKE_CXXFLAGS += -std=c++0x
}

SOURCES += main.cpp\
	UI/mainwindow.cpp \
    UI/telnetform.cpp \
    UI/fileform.cpp \
    UI/graphform.cpp \
    UI/clientinfodialog.cpp \

HEADERS  += UI/mainwindow.h \
    UI/telnetform.h \
    UI/fileform.h \
    UI/graphform.h \
    UI/clientinfodialog.h \


FORMS    += UI/mainwindow.ui \
    UI/telnetform.ui \
    UI/fileform.ui \
    UI/graphform.ui \
    UI/clientinfodialog.ui

LIBS += -L.. -ldelta3admin

RESOURCES += \
    Images/Images.qrc

