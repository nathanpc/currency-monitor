#include "mainwindow.h"
#include "trayicon.h"
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	TrayIcon trayIcon;
	trayIcon.show();

	// Open the settings window.
	MainWindow w;
	w.show();

	return a.exec();
}
