#include <QDebug>
#include <QMenu>

#include "trayicon.h"

TrayIcon::TrayIcon(QObject *parent) : QObject(parent) {
	trayIcon = new QSystemTrayIcon(parent);
	trayIcon->setIcon(QIcon(":/images/icon.png"));

	// TODO: Switch to this icon: http://www.iconarchive.com/show/icons8-metro-style-icons-by-visualpharm/Payment-Methods-Coins-icon.html

	qDebug() << "System Tray Available: " << trayIcon->isSystemTrayAvailable();
	qDebug() << "Supports Message: " << trayIcon->supportsMessages();

	populateMenu();
}

/**
 * Displays the tray icon.
 */
void TrayIcon::show() {
	trayIcon->show();
	//trayIcon->showMessage("Testing", "Message?");
	qDebug() << "Showing the tray icon.";
}

/**
 * Populates the menu.
 */
void TrayIcon::populateMenu() {
	QMenu *menu = new QMenu();

	// Settings action.
	QAction *settings_action = new QAction("Settings", menu);
	connect(settings_action, SIGNAL(triggered()), this, SLOT(openSettings()));
	menu->addAction(settings_action);

	trayIcon->setContextMenu(menu);
}

/**
 * Open the settings window.
 */
void TrayIcon::openSettings() {
	settings_window->show();
}
