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

	public:
		QSettings *settings;
		MainWindow *settings_window;

		explicit TrayIcon(QObject *parent = 0);

		void show();
		void notify(QString title, QString message);
		void populateMenu(QHash<QString, float> exchange);

	signals:
		void manualUpdateTriggered();

	public slots:
		void openSettings();
		void updateAll();
};

#endif // TRAYICON_H
