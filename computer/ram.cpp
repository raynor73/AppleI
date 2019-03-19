#include <QDebug>
#include <QFile>
#include <exception>
#include "ram.h"

/*static uint8_t program[] = {
	0xa9, 0x00, 0xaa, 0x20, 0xef, 0xff, 0xe8, 0x8a, 0x4c, 0x02, 0x00
};*/
/*static uint8_t program[] = {
	0xa9, 0xab, 0x20, 0xdc, 0xff, 0x00
};*/

Ram::Ram()
{
	QFile file("6502_functional_test.bin");
	if (!file.open(QIODevice::ReadOnly))
		throw std::runtime_error("Can't open test file");

	QByteArray fileData = file.readAll();
	for (uint32_t i = 0; i < 65536; i++)
	{
		m_ram[i] = fileData.data()[i];
	}
	/*for (uint16_t i = 0; i < sizeof(program); i++)
	{
		m_ram[i] = program[i];
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
