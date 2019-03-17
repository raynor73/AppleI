#include <QTimer>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"

//static

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Console *consoleWidget = new Console();
	setCentralWidget(consoleWidget);

	QTimer *timer = new QTimer();
	connect(timer, &QTimer::timeout, [] {

	});
	timer->start();
}

MainWindow::~MainWindow()
{
	delete ui;
}
