#include <QDebug>
#include "qtdisplay.h"

QtDisplay::QtDisplay(Console *consoleWidget, QObject *parent) :
	QObject(parent),
	m_consoleWidget(consoleWidget) {}

void QtDisplay::writeByte(const uint16_t address, const uint8_t value)
{
	/*if (!m_isDisplayReady) {
		return;
	}*/

	Display::writeByte(address, value);

	switch (address)
	{
	case DATA_PORT:
		m_charArray[0] = value & 0x7f;
		//qDebug("Display %c", m_charArray[0]);
		m_consoleWidget->putData(QByteArray(m_charArray, 1));
		break;

	case CONTROL_REGISTER_PORT:
		qDebug() << "Writing to display control register:" << hex << value;
		break;

	default:
		qDebug() << "Trying to write to unknown display port:" << hex << address << "value" << hex << value;
	}
}
