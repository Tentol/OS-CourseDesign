#-------------------------------------------------
#
# Project created by QtCreator 2019-02-20T20:12:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    system.h \
    cpu.h \
    mem.h \
    process.h

FORMS    += mainwindow.ui \
    mainwindow.ui
