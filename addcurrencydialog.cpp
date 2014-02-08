#include <QDebug>

#include "addcurrencydialog.h"
#include "ui_addcurrencydialog.h"

AddCurrencyDialog::AddCurrencyDialog(QWidget *parent) : QDialog(parent),
														ui(new Ui::AddCurrencyDialog) {
	ui->setupUi(this);
}

AddCurrencyDialog::~AddCurrencyDialog() {
	delete ui;
}

void AddCurrencyDialog::on_buttonBox_accepted() {
	QString from = ui->fromCurrency->text().toUpper();
	QString to   = ui->toCurrency->text().toUpper();

	qDebug() << "Add currency: " << from << " to " << to;
	emit currencyChanged(from, to);
}
