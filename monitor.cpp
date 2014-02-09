#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QStringList>

#include "monitor.h"

Monitor::Monitor(QSettings *settings, MainWindow *settings_window,
				 TrayIcon *trayIcon, QObject *parent) : QObject(parent) {
	this->settings = settings;
	this->trayIcon = trayIcon;
	this->settings_window = settings_window;
	connect(this->settings_window, SIGNAL(settingsChanged()), this, SLOT(settingsChanged()));

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTimeout()));

	if (settings->value("auto_update/enabled", true).toBool()) {
		timer->start(settings->value("auto_update/interval", 60).toInt() * 60000);
	}
}

/**
 * Updates everything.
 */
void Monitor::updateAll() {
	QHash<QString, QVariant> list = settings->value("exchange/list").toHash();

	for (int i = 0; i < list.keys().size(); ++i) {
		update(list.keys()[i]);
	}
}

/**
 * Updates a single exchange.
 *
 * @param name Ticker name.
 */
void Monitor::update(QString name) {
	qDebug() << "Updating:" << name;

	connect(&manager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(finishedRequest(QNetworkReply*)));

	QNetworkRequest request(buildYahooURL(name));
	manager.get(request);
}

/**
 * Got a response from Yahoo Finance.
 *
 * @param reply Server response.
 */
void Monitor::finishedRequest(QNetworkReply *reply) {
	QByteArray data = reply->readAll();
	QString name = reply->url().query().split('=')[1];

	data.remove(data.size() - 1 , 1);  // Remove the newline at the end.
	float value = QString(data).toFloat();

	qDebug() << "Currency ticker:" << name;
	qDebug() << "Currency value:" << value;

	values[name] = value;
	updateMenuAndNotify(name, value);
	emit updated(name, value);

	reply->deleteLater();
}

/**
 * Updates the tray icon menu and notify the user.
 *
 * @param name Ticker name.
 * @param value Exchange value.
 */
void Monitor::updateMenuAndNotify(QString name, float value) {
	bool notif_enabled = !settings->value("notification/enabled", false).toBool();
	QString notif_onupdate = settings->value("notification/trigger", "OnUpdate").toString();

	if (notif_enabled && (notif_onupdate == "OnUpdate")) {
		qDebug() << "Notify!";
		QString str_value;
		trayIcon->notify(name, str_value.sprintf("%.4f", value));
	}

	// TODO: Update the menu!
}

/**
 * Builds a URL to request from Yahoo.
 *
 * @param name Ticker name.
 * @return Yahoo Finance URL.
 */
QUrl Monitor::buildYahooURL(QString name) {
	QString url = "http://download.finance.yahoo.com/d/quotes.csv?s=" + name + "=X&e=.csv&f=l1";
	return QUrl(url);
}

/**
 * Time to update!
 */
void Monitor::updateTimeout() {
	qDebug() << "Timer timeout. Updating...";
	updateAll();
}

/**
 * Settings changed, better update the thing.
 */
void Monitor::settingsChanged() {
	bool auto_update = settings->value("auto_update/enabled", true).toBool();
	int interval = settings->value("auto_update/interval", 60).toInt();

	// Timer stuff.
	if (auto_update) {
		timer->start(interval * 60000);
	} else {
		timer->stop();
	}
}
