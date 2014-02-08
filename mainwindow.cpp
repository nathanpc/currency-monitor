#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
										  ui(new Ui::MainWindow) {
	ui->setupUi(this);
	populateSettings();
}

MainWindow::~MainWindow() {
	delete ui;
}

/**
 * Populates the view with the saved settings.
 */
void MainWindow::populateSettings() {
	// TODO: Populate the view with the settings.
}

/**
 * Hide the dialog.
 */
void MainWindow::on_buttonBox_rejected() {
	hide();
}

/**
 * Save and apply the settings.
 */
void MainWindow::on_buttonBox_accepted() {
	// Auto update.
	bool auto_update = ui->updateGroupBox->isChecked();
	int interval = ui->updateInterval->value();

	// Notification.
	bool notif_enabled = ui->noNotificationRadio->isChecked();
	bool notif_onupdate = ui->updateNotificationRadio->isChecked();

	// TODO: Save the settings.

	// Log the settings.
	qDebug() << "Saved the settings.";
	qDebug() << "Automatic update:" << auto_update;
	qDebug() << "Update interval: " << interval;
	qDebug() << "Notification enabled: " << notif_enabled;
	qDebug() << "Notify on update: " << notif_onupdate;

	// Hide the dialog.
	hide();
}
