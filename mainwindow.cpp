#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
										  ui(new Ui::MainWindow) {
	ui->setupUi(this);

	QPixmap icon = QPixmap(":/images/icon.png");
	qDebug() << icon.size();
	ui->label->setPixmap(icon);
}

MainWindow::~MainWindow() {
	delete ui;
}
