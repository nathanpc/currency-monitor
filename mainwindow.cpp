#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
										  ui(new Ui::MainWindow) {
	ui->setupUi(this);

	ui->lbl_appname->setText("Currency Monitor v" + QCoreApplication::applicationVersion());
}

MainWindow::~MainWindow() {
	delete ui;
}

/**
 * Populates the view with the saved settings.
 */
void MainWindow::populateSettings(QSettings *settings) {
	this->settings = settings;

	// Get the values from the settings.
	bool auto_update = settings->value("auto_update/enabled", true).toBool();
	int interval = settings->value("auto_update/interval", 60).toInt();
	bool notif_enabled = settings->value("notification/enabled", true).toBool();
	QString notif_onupdate = settings->value("notification/trigger", "OnUpdate").toString();

	// Populate the view.
	ui->updateGroupBox->setChecked(auto_update);
	ui->updateInterval->setValue(interval);
	ui->noNotificationRadio->setChecked(!notif_enabled);

	if (notif_onupdate == "OnUpdate") {
		ui->updateNotificationRadio->setChecked(true);
	}
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
	settings->setValue("auto_update/enabled", auto_update);
	settings->setValue("auto_update/interval", interval);

	// Notification.
	bool notif_enabled = ui->noNotificationRadio->isChecked();
	bool notif_onupdate = ui->updateNotificationRadio->isChecked();
	settings->setValue("notification/enabled", notif_enabled);
	if (notif_onupdate) {
		settings->setValue("notification/trigger", "OnUpdate");
	}

	// Save the settings.
	settings->sync();

	// Log the settings.
	qDebug() << "Saved the settings.";
	qDebug() << "Automatic update:" << auto_update;
	qDebug() << "Update interval: " << interval;
	qDebug() << "Notification enabled: " << notif_enabled;
	qDebug() << "Notify on update: " << notif_onupdate;

	// Hide the dialog.
	hide();
}
