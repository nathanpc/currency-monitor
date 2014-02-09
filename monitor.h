#ifndef MONITOR_H
#define MONITOR_H

#include <QObject>
#include <QSettings>
#include <QNetworkReply>
#include <QTimer>

#include "mainwindow.h"
#include "trayicon.h"

class Monitor : public QObject {
	Q_OBJECT

	private:
		QSettings *settings;
		MainWindow *settings_window;
		TrayIcon *trayIcon;

		QTimer *timer;
		QHash<QString, float> values;
		QNetworkAccessManager manager;

		QUrl buildYahooURL(QString name);
		void updateMenuAndNotify(QString name, float value);

	public:
		explicit Monitor(QSettings *settings, MainWindow *settings_window,
						 TrayIcon *trayIcon, QObject *parent = 0);

		void updateAll();
		void update(QString name);

	signals:
		void updated(QString name, float value);

	public slots:
		void finishedRequest(QNetworkReply *reply);
		void updateTimeout();
		void settingsChanged();
		void manualUpdate();

};

#endif // MONITOR_H
