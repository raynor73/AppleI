#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Console *consoleWidget = new Console();
	setCentralWidget(consoleWidget);

	QTimer *timer = new QTimer();
	timer->
}

MainWindow::~MainWindow()
{
	delete ui;
}
