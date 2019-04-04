#include <QTimer>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include <QException>
#include <map>
#include <vector>
#include "mainwindow.h"
#include "ui_mainwindow2.h"
#include "console.h"
#include "qtkeyboard.h"
#include "qtdisplay.h"
#include "test/testcase.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Mos6502::Cpu cpu;
	cpu.isDebugMode = true;

	TestMemory testMemory;
	cpu.memory = &testMemory;

	CpuState initialCpuState(0x00, 0x00, 0x00, 0x00, 0x0300, 0x00);

	std::map<uint16_t, uint8_t> initialMemoryState;
	initialMemoryState[0x0400] = 0x42;
	initialMemoryState[0x0000] = 0x00;
	initialMemoryState[0x0001] = 0x04;
	initialMemoryState[0x0300] = 0x01;
	initialMemoryState[0x0301] = 0x00;

	TestCase testCase(&cpu, &testMemory, initialCpuState, &initialMemoryState);
	testCase.performTest();
	qDebug(testCase.passed() ? "Test passed" : "Test failed");

	return;

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

	connect(ui->actionToggleDebug, &QAction::triggered, [computer, timer] {
		computer->toggleDebug();
		/*if (timer->isActive()) {
			timer->stop();
		} else {
			timer->start();
		}*/
	});
	connect(ui->actionCpuTick, &QAction::triggered, [computer] {
		computer->clockTick();
	});

	connect(ui->actionReset, &QAction::triggered, [computer] {
		computer->reset();
	});

	m_loadTxtModel = new LoadTxtModel(*keyboard);
	connect(ui->actionLoadTxt, &QAction::triggered, [this] {
		QString fileName = QFileDialog::getOpenFileName(this, "Open Text File", "~", "Text Files (*.txt)");
		QFile file(fileName);
		if (file.open(QIODevice::ReadOnly)) {
			m_loadTxtModel->onTextDataReceived(file.readAll());
		} else {
			QMessageBox msgBox;
			msgBox.setText("Can't open file");
			msgBox.exec();
		}
	});

	m_loadBinModel = new LoadBinModel(computer->ram());
	connect(ui->actionLoadBin, &QAction::triggered, [this] {
		QString fileName = QFileDialog::getOpenFileName(this, "Open Binary", "~", "Binary Files (*.rom *.bin)");
		QFile file(fileName);
		if (file.open(QIODevice::ReadOnly)) {
			m_loadBinModel->onDataReceived(file.readAll());
			uint16_t address = QInputDialog::getInt(
						this,
						"Start Address",
						"Start Address:",
						0xe000,
						0,
						0xffff
			);
			m_loadBinModel->onStartAddressProvided(address);
		} else {
			QMessageBox msgBox;
			msgBox.setText("Can't open file");
			msgBox.exec();
		}
	});
}

MainWindow::~MainWindow()
{
	delete ui;
}
