#include <QDebug>
#include "ram.h"

bool Ram::isUsingAddress(const uint16_t address)
{
	return address <= HIGHER_ADDRESS;
}

uint8_t Ram::readByte(const uint16_t address)
{
	if (address > HIGHER_ADDRESS) {
		qDebug("Trying to read from RAM address: 0x%04x", address);
		return 0;
	}

	return m_ram[address];
}

void Ram::writeByte(const uint16_t address, const uint8_t value)
{
	if (address > HIGHER_ADDRESS) {
		qDebug("Trying to write to RAM address: 0x%04x value: 0x%02x", address, value);
		return;
	}

	m_ram[address] = value;
}
