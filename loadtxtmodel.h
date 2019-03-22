#ifndef LOADTXTMODEL_H
#define LOADTXTMODEL_H

#include <QObject>
#include <QByteArray>
#include <QTimer>
#include "qtkeyboard.h"

class LoadTxtModel : public QObject
{
	Q_OBJECT
public:
	explicit LoadTxtModel(QtKeyboard &keyboard, QObject *parent = nullptr);

	int getState()
	{
		return m_state;
	}

	static const int STATE_AWAITING_TEXT_DATA = 1;
	static const int STATE_SIMULATING_KEYSTROKES = 2;

signals:
	void state(const int state);

public slots:
	void onTextDataReceived(QByteArray textData);

private:
	int m_state;
	int m_currentTextPosition;

	QTimer m_keystrokeTimer;
	QByteArray m_textData;
	QtKeyboard &m_keyboard;

	void changeState(const int newState);
};

#endif // LOADTXTMODEL_H
