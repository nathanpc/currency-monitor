#-------------------------------------------------
#
# Project created by QtCreator 2014-02-07T23:43:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CurrencyMonitor
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp \
	trayicon.cpp \
	addcurrencydialog.cpp \
	monitor.cpp

HEADERS  += mainwindow.h \
	trayicon.h \
	addcurrencydialog.h \
	monitor.h

FORMS    += mainwindow.ui \
	addcurrencydialog.ui

RESOURCES += \
	images.qrc

ICON = images/icon.png
