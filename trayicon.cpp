#include <QDebug>

#include "trayicon.h"

TrayIcon::TrayIcon(QObject *parent) : QObject(parent) {
	trayIcon = new QSystemTrayIcon(parent);
	trayIcon->setIcon(QIcon(":/images/icon.png"));

	// TODO: Switch to this icon: http://www.iconarchive.com/show/icons8-metro-style-icons-by-visualpharm/Payment-Methods-Coins-icon.html

	qDebug() << "System Tray Available: " << trayIcon->isSystemTrayAvailable();
	qDebug() << "Supports Message: " << trayIcon->supportsMessages();
}

void TrayIcon::show() {
	trayIcon->show();
	//trayIcon->showMessage("Testing", "Message?");
	qDebug() << "Showing the tray icon.";
}
