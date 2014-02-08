#include <QApplication>
#include <QSettings>

#include "mainwindow.h"
#include "trayicon.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	a.setApplicationDisplayName("Currency Monitor");
	a.setApplicationVersion("1.0");

	// Setup the settings.
	QSettings *settings = new QSettings("DreamInTech", "CurrencyMonitor");

	// Initialize the settings window.
	MainWindow w;
	w.setWindowFlags(Qt::Dialog | Qt::Desktop);
	w.populateSettings(settings);

	// Show the tray icon.
	TrayIcon trayIcon;
	trayIcon.settings = settings;
	trayIcon.settings_window = &w;
	trayIcon.show();

	return a.exec();
}
