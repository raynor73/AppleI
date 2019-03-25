#include <QDebug>
#include "display.h"

Display::Display() : m_isDisplayReady(true) {}

uint8_t Display::readByte(const uint16_t address)
{
	switch (address) {
	case DATA_PORT: {
		uint8_t value = m_isDisplayReady ? 0x8f : 0x7f;
		m_isDisplayReady = true;
		return value;
	}

	case CONTROL_REGISTER_PORT:
		qDebug() << "Reading from display control register";
		return 0;

	default:
		qDebug() << "Trying to read from unknown display port:" << hex << address;
		return 0;
	}
}

void Display::writeByte(const uint16_t address, const uint8_t value)
{
	switch (address) {
	case DATA_PORT:
		m_isDisplayReady = false;
		break;

	case CONTROL_REGISTER_PORT:
		qDebug("Writing to control display port: 0x%04x value: 0x%02x", address, value);
		break;

	default:
		qDebug("Trying to write to unknown display port: 0x%04x value: 0x%02x", address, value);
		break;
	}
}

bool Display::isUsingAddress(const uint16_t address)
{
	return address == DATA_PORT || address == CONTROL_REGISTER_PORT;
}
