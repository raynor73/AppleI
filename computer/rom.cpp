#include <QDebug>
#include "rom.h"

Rom::Rom()
{
	// NMI vector
	m_rom[0xfa] = 0x00;
	m_rom[0xfb] = 0x0f;

	// Reset vector
	m_rom[0xfc] = 0x00;
	m_rom[0xfd] = 0xff;

	// IRQ vector
	m_rom[0xfe] = 0x00;
	m_rom[0xff] = 0x00;
}

bool Rom::isUsingAddress(const uint16_t address)
{
	return address >= LOWER_ADDRESS;
}

uint8_t Rom::readByte(const uint16_t address)
{
	if (address < LOWER_ADDRESS) {
		qDebug() << "Trying to read from ROM address:" << hex << address;
		return 0;
	}

	return m_rom[address & 0xff];
}

void Rom::writeByte(const uint16_t address, const uint8_t value)
{
	qDebug() << "Trying to write to ROM address:" << hex << address << "value:" << hex << value;
}
