#include <QDebug>
#include "rom.h"

static uint8_t program[] = {
	0xd8,            //RESET     CLD
	0x58,            //          CLI
	0xa0, 0x7f,      //          LDY #$7f
	0x8c, 0x12, 0xd0,//          STY DSP
	0xa9, 0xa7,      //          LDA #$a7
	0x8d, 0x11, 0xd0,//          STA KBD CR
	0x8d, 0x13, 0xd0,//          STA DSP CR
	0xc9, 0xdf,      //NOTCR     CMP #$DF
	0xf0, 0x03,      //          BEQ ESCAPE
	0xc8,            //          INY
};

Rom::Rom()
{
	for (uint16_t i = 0; i < sizeof(program); i++) {
		m_rom[i] = program[i];
	}

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
