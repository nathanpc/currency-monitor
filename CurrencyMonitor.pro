#-------------------------------------------------
#
# Project created by QtCreator 2014-02-07T23:43:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CurrencyMonitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    trayicon.cpp

HEADERS  += mainwindow.h \
    trayicon.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

OTHER_FILES +=
