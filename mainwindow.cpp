#include <QTimer>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "qtkeyboard.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Console *consoleWidget = new Console();
	setCentralWidget(consoleWidget);

	QTimer *timer = new QTimer();
	QtKeyboard *keyboard = new QtKeyboard();
	Computer *computer = new Computer(keyboard);
	consoleWidget->installEventFilter(keyboard);
	connect(timer, &QTimer::timeout, [computer] {
		computer->clockTick();
	});
	timer->start();
}

MainWindow::~MainWindow()
{
	delete ui;
}
