#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

	private:
		Ui::MainWindow *ui;

	public:
		QSettings *settings;

		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

		void populateSettings(QSettings *settings);
		void populateList();

	signals:
		void settingsChanged();

	private slots:
		void addCurrency(QString from, QString to);

		void on_buttonBox_rejected();
		void on_buttonBox_accepted();
		void on_updateGroupBox_toggled(bool on);
		void on_btAddCurrency_clicked();
		void on_btRemoveCurrency_clicked();
};

#endif // MAINWINDOW_H
