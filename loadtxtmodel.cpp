#include <QException>
#include "loadtxtmodel.h"

LoadTxtModel::LoadTxtModel(QtKeyboard &keyboard, QObject *parent) :
	QObject(parent),
	m_state(STATE_AWAITING_TEXT_DATA),
	m_keyboard(keyboard)
{
	m_keystrokeTimer.setInterval(5);
	connect(&m_keystrokeTimer, &QTimer::timeout, [this] {
		if (m_state == STATE_SIMULATING_KEYSTROKES) {
			if (m_keyboard.simulateKeystroke(uint8_t(m_textData.at(m_currentTextPosition)))) {
				m_currentTextPosition++;
				if (m_currentTextPosition == m_textData.size()) {
					changeState(STATE_AWAITING_TEXT_DATA);
				}
			}
		}
	});
}

void LoadTxtModel::onTextDataReceived(QByteArray textData)
{
	if (m_state == STATE_AWAITING_TEXT_DATA)
	{
		changeState(STATE_SIMULATING_KEYSTROKES);
		m_textData = textData;
		m_currentTextPosition = 0;
		if (!m_keystrokeTimer.isActive()) {
			m_keystrokeTimer.start();
		}
	}
}

void LoadTxtModel::changeState(const int newState)
{
	if (m_state == newState)
	{
		throw QException();
	}

	m_state = newState;
	emit state(m_state);
}
