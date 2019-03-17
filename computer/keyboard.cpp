#include <QDebug>
#include "keyboard.h"

Keyboard::Keyboard() : m_hasKeyToRead(false) {}

uint8_t Keyboard::readByte(const uint16_t address)
{
	switch (address) {
	case DATA_PORT:
		m_hasKeyToRead = false;
		return m_keyCode;

	case CONTROL_REGISTER_PORT:
		return m_hasKeyToRead ? 0x80 : 0x00;

	default:
		qDebug() << "Trying to read from unknown keboard port:" << hex << address;
		return 0;
	}
}

void Keyboard::writeByte(const uint16_t address, const uint8_t value)
{
	qDebug() << "Trying to write to keboard port:" << hex << address << "value" << hex << value;
}

bool Keyboard::isUsingAddress(const uint16_t address)
{
	return address == DATA_PORT || address == CONTROL_REGISTER_PORT;
}
