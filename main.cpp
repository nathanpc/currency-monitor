#include "mainwindow.h"
#include "trayicon.h"
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	// TODO: Get a global QSettings and pass it to both.

	// Initialize the settings window.
	MainWindow w;
	w.setWindowFlags(Qt::Dialog | Qt::Desktop);

	// Show the tray icon.
	TrayIcon trayIcon;
	trayIcon.show();

	// Open the settings window.
	w.show();

	return a.exec();
}
