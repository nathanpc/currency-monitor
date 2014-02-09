#include <QDebug>
#include <QMenu>

#include "trayicon.h"

TrayIcon::TrayIcon(QObject *parent) : QObject(parent) {
	trayIcon = new QSystemTrayIcon(parent);
	trayIcon->setIcon(QIcon(":/images/icon.png"));

	// TODO: Switch to this icon: http://www.iconarchive.com/show/icons8-metro-style-icons-by-visualpharm/Payment-Methods-Coins-icon.html

	qDebug() << "System Tray Available: " << trayIcon->isSystemTrayAvailable();
	qDebug() << "Supports Message: " << trayIcon->supportsMessages();

	QHash<QString, float> empty;
	populateMenu(empty);
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
 * Pops up a notification.
 *
 * @param title Notification title.
 * @param message Notification message.
 */
void TrayIcon::notify(QString title, QString message) {
	trayIcon->showMessage(title, message);
}

/**
 * Populates the menu.
 *
 * @param exchange Currency hash.
 */
void TrayIcon::populateMenu(QHash<QString, float> exchange) {
	QMenu *menu = new QMenu();

	// Update action.
	QAction *update_action = new QAction("Update", menu);
	connect(update_action, SIGNAL(triggered()), this, SLOT(updateAll()));
	menu->addAction(update_action);

	menu->addSeparator();
	for (int i = 0; i < exchange.keys().size(); ++i) {
		QString ticker = exchange.keys()[i];
		QString text;
		text.sprintf("%s\t%.4f", ticker.toStdString().c_str(), exchange[ticker]);

		QAction *exchange_action = new QAction(text, menu);
		menu->addAction(exchange_action);
	}
	menu->addSeparator();

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

/**
 * Manual update.
 */
void TrayIcon::updateAll() {
	emit manualUpdateTriggered();
}
