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
}

MainWindow::~MainWindow()
{
	delete ui;
}
