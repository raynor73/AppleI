#include <QTimer>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QException>
#include "mainwindow.h"
#include "ui_mainwindow2.h"
#include "console.h"
#include "qtkeyboard.h"
#include "qtdisplay.h"
#include "enhancedbasic.h"

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
	//timer->setInterval(100);
	connect(timer, &QTimer::timeout, [computer] {
		computer->clockTick();
	});
	timer->start();

	connect(ui->actionReset, &QAction::triggered, [computer] {
		computer->reset();
	});

	m_loadTxtModel = new LoadTxtModel(*keyboard);
	connect(ui->actionLoadTxt, &QAction::triggered, [this] {
		//m_loadTxtModel->onTextDataReceived(QByteArray(enhancedBasicTextData));
	});

	m_loadBinModel = new LoadBinModel(computer->ram());
	connect(ui->actionLoadBin, &QAction::triggered, [this] {
		QString fileName = QFileDialog::getOpenFileName(this, "Open Binary", "~", "Binary Files (*.rom *.bin)");
		QFile file(fileName);
		m_loadBinModel->onDataReceived(file.readAll());

	});
}

MainWindow::~MainWindow()
{
	delete ui;
}
