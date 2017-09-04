#-------------------------------------------------
#
# Project created by QtCreator 2016-10-06T09:49:40
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChaChat
TEMPLATE = app


SOURCES += main.cpp\
    mainpage.cpp \
    chatpage.cpp \
    registerpage.cpp \
    tcpserverwidget.cpp \
    server.cpp \
    tcpsocket.cpp \
    adminpage.cpp

HEADERS  += \
    mainpage.h \
    chatpage.h \
    registerpage.h \
    tcpserverwidget.h \
    server.h \
    tcpsocket.h \
    adminpage.h

FORMS    += \
    registerpage.ui \
    mainpage.ui \
    chatpage.ui \
    tcpserverwidget.ui \
    adminpage.ui
