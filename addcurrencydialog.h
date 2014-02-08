#ifndef ADDCURRENCYDIALOG_H
#define ADDCURRENCYDIALOG_H

#include <QDialog>

namespace Ui {
	class AddCurrencyDialog;
}

class AddCurrencyDialog : public QDialog {
	Q_OBJECT

	private:
		Ui::AddCurrencyDialog *ui;

	public:
		explicit AddCurrencyDialog(QWidget *parent = 0);
		~AddCurrencyDialog();

	private slots:
		void on_buttonBox_accepted();

	signals:
		void currencyChanged(QString from, QString to);
};

#endif // ADDCURRENCYDIALOG_H
