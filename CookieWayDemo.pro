#-------------------------------------------------
#
# Project created by QtCreator 2016-02-29T15:50:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CookieWayDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagereader.cpp \
    surveyfiller.cpp

HEADERS  += mainwindow.h \
    imagereader.h \
    surveyfiller.h

LIBS += -llept -ltesseract

FORMS    += mainwindow.ui
