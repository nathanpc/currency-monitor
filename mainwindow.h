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

	public:
		QSettings *settings;

		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

		void populateSettings(QSettings *settings);

	private slots:
		void on_buttonBox_rejected();
		void on_buttonBox_accepted();

	private:
		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
