#include <QTimer>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow2.h"
#include "console.h"
#include "qtkeyboard.h"
#include "qtdisplay.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Console *consoleWidget = new Console();
	setCentralWidget(consoleWidget);

	QTimer *timer = new QTimer();
	QtKeyboard *keyboard = new QtKeyboard();
	QtDisplay *display = new QtDisplay(consoleWidget);
	Computer *computer = new Computer(keyboard, display);
	consoleWidget->installEventFilter(keyboard);
	timer->setInterval(100);
	connect(timer, &QTimer::timeout, [computer] {
		computer->clockTick();
	});
	timer->start();

	connect(ui->actionReset, &QAction::triggered, [computer] {
		computer->reset();
	});
}

MainWindow::~MainWindow()
{
	delete ui;
}
