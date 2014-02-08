#include <QDebug>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addcurrencydialog.h"

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

	// Populate the list.
	populateList();
}

/**
 * Populates the exchange list.
 */
void MainWindow::populateList() {
	QHash<QString, QVariant> list = settings->value("exchange/list").toHash();
	ui->currencyList->clear();

	for (int i = 0; i < list.keys().size(); ++i) {
		QString ticker = list.keys()[i];
		QString display_name = list[ticker].toString();

		QListWidgetItem *list_item = new QListWidgetItem(display_name, ui->currencyList);
		list_item->setToolTip(ticker);
		ui->currencyList->addItem(list_item);
	}
}

/**
 * Hide the dialog.
 */
void MainWindow::on_buttonBox_rejected() {
	close();
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
	close();
}

/**
 * Auto update enable checkbox toogled.
 *
 * @param on Checkbox is checked?
 */
void MainWindow::on_updateGroupBox_toggled(bool on) {
	if (on) {
		ui->updateInterval->setEnabled(true);
	} else {
		ui->updateInterval->setEnabled(false);
	}
}

/**
 * Opens the currency add dialog.
 */
void MainWindow::on_btAddCurrency_clicked() {
	AddCurrencyDialog *dialog = new AddCurrencyDialog(this);
	connect(dialog, SIGNAL(currencyChanged(QString, QString)),
			this, SLOT(addCurrency(QString, QString)));
	dialog->show();
}

/**
 * Adds a currency.
 *
 * @param from From currency.
 * @param to To currency.
 */
void MainWindow::addCurrency(QString from, QString to) {
	QString name = from + to;
	QString display = from + " to " + to;

	// Grab the list.
	qDebug() << "Adding to the settings:" << name << display;
	QHash<QString, QVariant> list = settings->value("exchange/list").toHash();

	// Append the new item.
	list[name] = display;

	// Store it.
	settings->setValue("exchange/list", list);
	settings->sync();

	populateList();
}

/**
 * Removes a currency.
 */
void MainWindow::on_btRemoveCurrency_clicked() {
	QString name = ui->currencyList->selectedItems().first()->toolTip();
	qDebug() << "Deleting:" << name;

	QHash<QString, QVariant> list = settings->value("exchange/list").toHash();
	list.remove(name);
	settings->setValue("exchange/list", list);
	settings->sync();

	populateList();
}
