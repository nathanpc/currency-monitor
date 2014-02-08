#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QSettings>

#include "mainwindow.h"

class TrayIcon : public QObject {
	Q_OBJECT

	private:
		QSystemTrayIcon *trayIcon;

		void populateMenu();

	public:
		QSettings *settings;
		MainWindow *settings_window;

		explicit TrayIcon(QObject *parent = 0);

		void show();

	signals:

	public slots:
		void openSettings();
};

#endif // TRAYICON_H
