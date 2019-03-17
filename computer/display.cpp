#include <QDebug>
#include "display.h"

uint8_t Display::readByte(const uint16_t address)
{
	switch (address) {
	case DATA_PORT:
		return 0x80;

	case CONTROL_REGISTER_PORT:
		qDebug() << "Reading from display control register";
		return 0;

	default:
		qDebug() << "Trying to read from unknown display port:" << hex << address;
		return 0;
	}
}

bool Display::isUsingAddress(const uint16_t address)
{
	return address == DATA_PORT || address == CONTROL_REGISTER_PORT;
}
