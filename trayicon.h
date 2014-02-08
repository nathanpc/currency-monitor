#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QSettings>

class TrayIcon : public QObject {
	Q_OBJECT

	private:
		QSystemTrayIcon *trayIcon;

	public:
		QSettings *settings;

		explicit TrayIcon(QObject *parent = 0);

		void show();

	signals:

	public slots:

};

#endif // TRAYICON_H
