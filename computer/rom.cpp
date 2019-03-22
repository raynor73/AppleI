#include <QDebug>
#include <QFile>
#include <QByteArray>
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
	0xf0, 0x13,      //          BEQ BACKSPACE
	0xc9, 0x9b,      //          CMP #$9b
	0xf0, 0x03,      //          BEQ ESCAPE
	0xc8,            //          INY
	0x10, 0x0f,      //          BPL NEXTCHAR
	0xa9, 0xdc,      //ESCAPE    LDA #$DC
	0x20, 0xef, 0xff,//          JSR ECHO
	0xa9, 0x8d,      //GETLINE   LDA #$8d
	0x20, 0xef, 0xff,//          JSR ECHO
	0xa0, 0x01,      //          LDY #$01
	0x88,            //BACKSPACE DEY
	0x30, 0xf6,      //          BMI GETLINE
	0xad, 0x11, 0xd0,//NEXTCHAR  LDA KBD CR
	0x10, 0xfb,      //          BPL NEXTCHAR
	0xad, 0x10, 0xd0,//          LDA KBD
	0x99, 0x00, 0x02,//          STA IN, Y
	0x20, 0xef, 0xff,//          JSR ECHO
	0xc9, 0x8d,      //          CMP #$8d
	0xd0, 0xd4,      //          BNE NOTCR
	0xa0, 0xff,      //          LDY #$ff
	0xa9, 0x00,      //          LDA #$00
	0xaa,            //          TAX
	0x0a,            //SETSTOR   ASL
	0x85, 0x2b,      //SETMODE   STA MODE
	0xc8,            //BLSKIP    INY
	0xb9, 0x00, 0x02,//NEXT ITEM LDA IN, Y
	0xc9, 0x8d,      //          CMP #8d
	0xf0, 0xd4,      //          BEQ GETLINE
	0xc9, 0xae,      //          CMP #$ae
	0x90, 0xf4,      //          BCC BLSKIP
	0xf0, 0xf0,      //          BEQ SETMODE
	0xc9, 0xba,      //          CMP #$ba
	0xf0, 0xeb,      //          BEQ SETSTOR
	0xc9, 0xd2,      //          CMP #$d2
	0xf0, 0x3b,      //          BEQ RUN
	0x86, 0x28,      //          STX L
	0x86, 0x29,      //          STX H
	0x84, 0x2a,      //          STY YSAV
	0xb9, 0x00, 0x02,//NEXTHEX   LDA IN, Y
	0x49, 0xb0,      //          EOR #$b0
	0xc9, 0x0a,      //          CMP #$0a
	0x90, 0x06,      //          BCC DIG
	0x69, 0x88,      //          ADC #$88
	0xc9, 0xfa,      //          CMP #$fa
	0x90, 0x11,      //           BCC NOTHEX
	0x0a,            //DIG        ASL
	0x0a,            //           ASL
	0x0a,            //           ASL
	0x0a,            //           ASL
	0xa2, 0x04,      //           LDX #$04
	0x0a,            //HEXSHIFT   ASL
	0x26, 0x28,      //           ROL L
	0x26, 0x29,      //           ROL H
	0xca,            //           DEX
	0xd0, 0xf8,      //           BNE HEXSHIFT
	0xc8,            //           INY
	0xd0, 0xe0,      //           BNE NEXTHEX
	0xc4, 0x2a,      //NOTHEX     CPY YSAV
	0xf0, 0x97,      //           BEQ ESCAPE
	0x24, 0x2b,      //           BIT MODE
	0x50, 0x10,      //           BVC NOTSTOR
	0xa5, 0x28,      //           LDA L
	0x81, 0x26,      //           STA (STL, X)
	0xe6, 0x26,      //           INC STL
	0xd0, 0xb5,      //           BNE NEXTITEM
	0xe6, 0x27,      //           INC STH
	0x4c, 0x44, 0xff,//TONEXTITEM JMP NEXTITEM
	0x6c, 0x24, 0x00,//RUN        JMP (XAML)
	0x30, 0x2b,      //NOTSTOR    BMI XAMNEXT
	0xa2, 0x02,      //           LDX #$02
	0xb5, 0x27,      //SETADR     LDA L-1, X
	0x95, 0x25,      //           STA STL-1, X
	0x95, 0x23,      //           STA XAML-1, X
	0xca,            //           DEX
	0xd0, 0xf7,      //           BNE SETADR
	0xd0, 0x14,      //NXTPRNT    BNE PRDATA
	0xa9, 0x8d,      //           LDA #$8d
	0x20, 0xef, 0xff,//           JSR ECHO
	0xa5, 0x25,      //           LDA XAMH
	0x20, 0xdc, 0xff,//           JSR PRBYTE
	0xa5, 0x24,      //           LDA XAML
	0x20, 0xdc, 0xff,//           JSR PRBYTE
	0xa9, 0xba,      //           LDA #$ba
	0x20, 0xef, 0xff,//           JSR ECHO
	0xa9, 0xa0,      //PRDATA     LDA #$a0
	0x20, 0xef, 0xff,//           JSR ECHO
	0xa1, 0x24,      //           LDA (XAML, X)
	0x20, 0xdc, 0xff,//           JSR PRBYTE
	0x86, 0x2b,      //XAMNEXT    STX MODE
	0xa5, 0x24,      //           LDA XAML
	0xc5, 0x28,      //           CMP L
	0xa5, 0x25,      //           LDA XAMH
	0xe5, 0x29,      //           SBC H
	0xb0, 0xc1,      //           BCS TONEXTITEM
	0xe6, 0x24,      //           INC XAML
	0xd0, 0x02,      //           BNE MOD8CHK
	0xe6, 0x25,      //           INC XAML
	0xa5, 0x24,      //MOD8CHK....LDA XAML
	0x29, 0x07,      //           AND #$07
	0x10, 0xc8,      //           BPL NXTPRNT
	0x48,            //PRBYTE     PHA
	0x4a,            //           LSR
	0x4a,            //           LSR
	0x4a,            //           LSR
	0x4a,            //           LSR
	0x20, 0xe5, 0xff,//           JSR PRHEX
	0x68,            //           PLA
	0x29, 0x0f,      //           AND #$0f
	0x09, 0xb0,      //           ORA #$b0
	0xc9, 0xba,      //           CMP #$ba
	0x90, 0x02,      //           BCC ECHO
	0x69, 0x06,      //           ADC #$06
	0x2c, 0x12, 0xd0,//ECHO      BIT DSP
	0xea, 0xea,      //          BMI ECHO (NOPed 0x30, 0xfb)
	0x8d, 0x12, 0xd0,//          STA DSP
	0x60,            //          RTS
	0x00, 0x00,      //(unused)
	0x00, 0x0f,      //(NMI)
	0x00, 0xff,      //(RESET)
	0x00, 0x00       //(IRQ)
};

Rom::Rom()
{
	/*for (uint16_t i = 0; i < sizeof(program); i++)
	{
		m_rom[i] = program[i];
	}*/
	QFile file("applesoft-lite-0.4.bin");
	if (!file.open(QIODevice::ReadOnly))
		throw std::runtime_error("Can't open ROM file");

	QByteArray fileData = file.readAll();
	for (int i = 0; i < fileData.size(); i++)
	{
		m_rom[i] = uint8_t(fileData.data()[i]);
	}
	m_rom[0xfff2 - LOWER_ADDRESS] = 0xea;
	m_rom[0xfff3 - LOWER_ADDRESS] = 0xea;
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

	return m_rom[address - LOWER_ADDRESS];
}

void Rom::writeByte(const uint16_t address, const uint8_t value)
{
	qDebug() << "Trying to write to ROM address:" << hex << address << "value:" << hex << value;
}
