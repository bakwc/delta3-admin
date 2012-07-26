#-------------------------------------------------
#
# Project created by QtCreator 2012-07-10T11:36:26
#
#-------------------------------------------------

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


QT += core network gui
TARGET = delta3admin
TEMPLATE = lib
DESTDIR = ..

QMAKE_CXXFLAGS += -std=c++0x


SOURCES += network.cpp \
    client.cpp \
    netextract.cpp \
    Protocols/abstrproto.cpp \
    Protocols/telnet.cpp \
    Protocols/graphics.cpp \
    Protocols/file.cpp \
    Protocols/Proxy/proxyserver.cpp \
    Protocols/Proxy/proxy.cpp \
    Protocols/Proxy/proxythread.cpp


HEADERS  += network.h \
    client.h \
    defines.h \
    utils.h \
    netextract.h \
    Protocols/abstrproto.h \
    Protocols/telnet.h \
    Protocols/graphics.h \
    Protocols/file.h \
    Protocols/Proxy/proxyserver.h \
    Protocols/Proxy/proxy.h \
    Protocols/Proxy/proxythread.h

#SOURCES +=  UI/fileform.cpp \
#	    UI/graphform.cpp \
#	    UI/clientinfodialog.cpp \
#	    UI/telnetform.cpp \
#	    UI/mainwindow.cpp \
#	    main.cpp\

#HEADERS +=  UI/mainwindow.h \
#	    UI/fileform.h \
#	    UI/graphform.h \
#	    UI/clientinfodialog.h \
#	    UI/telnetform.h \


#FORMS += UI/mainwindow.ui \
#	 UI/telnetform.ui \
#	 UI/fileform.ui \
#	 UI/graphform.ui \
#	 UI/clientinfodialog.ui
