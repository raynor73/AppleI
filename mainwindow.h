#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "computer/computer.h"
#include "loadtxtmodel.h"
#include "loadbinmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	LoadTxtModel *m_loadTxtModel;
	LoadBinModel *m_loadBinModel;
};

#endif // MAINWINDOW_H
