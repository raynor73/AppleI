#include <QDebug>
#include <QFile>
#include <exception>
#include "ram.h"

Ram::Ram()
{
	/*QFile file("6502_decimal_test.bin");
	if (!file.open(QIODevice::ReadOnly))
		throw std::runtime_error("Can't open test file");

	QByteArray fileData = file.readAll();
	for (uint32_t i = 0; i < fileData.size(); i++)
	{
		m_ram[0x4000 + i] = uint8_t(fileData.data()[i]);
	}*/
	/*for (int i = 0; i < 0x100; i++) {
		m_ram[i] = 0x03;
	}*/
}

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
