#include <QDebug>
#include "cpu6502.h"
#include "utils/debug.h"

Cpu6502::Cpu6502() : m_isUndefinedState(false) {}

void Cpu6502::clockTick()
{
	if (m_isUndefinedState) {
		return;
	}

	uint8_t opcode = memory->readByte(pc);
	uint16_t address;
	uint16_t address2;
	switch (opcode) {
	case 0x18:
		cpuDebug("CLC");
		p &= ~CARRY_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0x38:
		cpuDebug("SEC");
		p |= CARRY_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0x58:
		cpuDebug("CLI");
		p &= ~INTERRUPT_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0x78:
		cpuDebug("SEI");
		p |= INTERRUPT_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0x81:
		cpuDebug("STA Indexed Indirect");
		pc++;
		address = (memory->readByte(pc) + x) & 0xff;
		address2 = memory->readByte(address);
		address2 |= memory->readByte(address + 1) << 8;
		memory->writeByte(address2, a);
		m_operationTime = 6;
		pc++;
		break;

	case 0x84:
		cpuDebug("STY Zero Page");
		pc++;
		memory->writeByte(memory->readByte(pc), y);
		m_operationTime = 3;
		pc++;
		break;

	case 0x85:
		cpuDebug("STA Zero Page");
		pc++;
		memory->writeByte(memory->readByte(pc), a);
		m_operationTime = 3;
		pc++;
		break;

	case 0x8c:
		cpuDebug("STY Absolute");
		pc++;
		address = memory->readByte(pc);
		pc++;
		address |= memory->readByte(pc) << 8;
		memory->writeByte(address, y);
		m_operationTime = 4;
		pc++;
		break;

	case 0x8d:
		cpuDebug("STA Absolute");
		pc++;
		address = memory->readByte(pc);
		pc++;
		address |= memory->readByte(pc) << 8;
		memory->writeByte(address, a);
		m_operationTime = 4;
		pc++;
		break;

	case 0x91:
		cpuDebug("STA Indirect Indexed");
		pc++;
		address = memory->readByte(pc);
		address2 = memory->readByte(address);
		address2 |= memory->readByte((address + 1) & 0xff);
		memory->writeByte(address2 + y, a);
		m_operationTime = 6;
		pc++;
		break;

	case 0x94:
		cpuDebug("STY Zero Page Indexed X");
		pc++;
		memory->writeByte((memory->readByte(pc) + x) & 0xff, y);
		m_operationTime = 4;
		pc++;
		break;

	case 0x95:
		cpuDebug("STA Zero Page Indexed X");
		pc++;
		memory->writeByte((memory->readByte(pc) + x) & 0xff, a);
		m_operationTime = 4;
		pc++;
		break;

	case 0x99:
		cpuDebug("STA Absolute Indexed Y");
		pc++;
		address = memory->readByte(pc);
		pc++;
		address |= memory->readByte(pc) << 8;
		memory->writeByte(address + y, a);
		m_operationTime = 5;
		pc++;
		break;

	case 0x9d:
		cpuDebug("STA Absolute Indexed X");
		pc++;
		address = memory->readByte(pc);
		pc++;
		address |= memory->readByte(pc) << 8;
		memory->writeByte(address + x, a);
		m_operationTime = 5;
		pc++;
		break;

	case 0xa0:
		cpuDebug("LDY Immediate");
		pc++;
		y = memory->readByte(pc);
		m_operationTime = 2;
		updateSzFlags(y);
		pc++;
		break;

	case 0xa1:
		cpuDebug("LDA Indexed Indirect");
		pc++;
		address = (memory->readByte(pc) + x) & 0xff;
		address2 = memory->readByte(address);
		address2 |= memory->readByte(address + 1) << 8;
		a = memory->readByte(address2);
		m_operationTime = 6;
		updateSzFlags(a);
		pc++;
		break;

	case 0xa4:
		cpuDebug("LDY Zero Page");
		pc++;
		y = memory->readByte(memory->readByte(pc));
		m_operationTime = 3;
		updateSzFlags(y);
		pc++;
		break;

	case 0xac:
		cpuDebug("LDY Absolute");
		pc++;
		address = memory->readByte(pc);
		pc++;
		address |= memory->readByte(pc) << 8;
		y = memory->readByte(address);
		m_operationTime = 4;
		updateSzFlags(y);
		pc++;
		break;

	case 0xa5:
		cpuDebug("LDA Zero Page");
		pc++;
		a = memory->readByte(memory->readByte(pc));
		m_operationTime = 3;
		updateSzFlags(a);
		pc++;
		break;

	case 0xa9:
		cpuDebug("LDA Immediate");
		pc++;
		a = memory->readByte(pc);
		m_operationTime = 2;
		updateSzFlags(a);
		pc++;
		break;

	case 0xad:
		cpuDebug("LDA Absolute");
		pc++;
		address = memory->readByte(pc);
		pc++;
		address |= memory->readByte(pc) << 8;
		a = memory->readByte(address);
		m_operationTime = 4;
		updateSzFlags(a);
		pc++;
		break;

	case 0xb1:
		cpuDebug("LDA Indirect Indexed");
		pc++;
		address = memory->readByte(pc);
		address2 = memory->readByte(address);
		address2 |= memory->readByte((address + 1) & 0xff);
		m_operationTime = (address2 & 0xff) + y > 0xff ? 6 : 5;
		a = memory->readByte(address2 + y);
		updateSzFlags(a);
		pc++;
		break;

	case 0xb4:
		cpuDebug("LDY Zero Page Indexed");
		pc++;
		y = memory->readByte((memory->readByte(pc) + x) & 0xff);
		m_operationTime = 4;
		updateSzFlags(y);
		pc++;
		break;

	case 0xb5:
		cpuDebug("LDA Zero Page Indexed");
		pc++;
		a = memory->readByte((memory->readByte(pc) + x) & 0xff);
		m_operationTime = 4;
		updateSzFlags(a);
		pc++;
		break;

	case 0xb8:
		cpuDebug("CLV");
		p &= ~OVERFLOW_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0xb9:
		cpuDebug("LDA Absolute Indexed Y");
		pc++;
		address = memory->readByte(pc);
		pc++;
		address |= memory->readByte(pc) << 8;
		m_operationTime = (address & 0xff) + y > 0xff ? 5 : 4;
		a = memory->readByte(address + y);
		updateSzFlags(a);
		pc++;
		break;

	case 0xbc:
		cpuDebug("LDY Absolute Indexed");
		pc++;
		address = memory->readByte(pc);
		pc++;
		address |= memory->readByte(pc) << 8;
		m_operationTime = (address & 0xff) + x > 0xff ? 5 : 4;
		y = memory->readByte(address + x);
		updateSzFlags(y);
		pc++;
		break;

	case 0xbd:
		cpuDebug("LDA Absolute Indexed X");
		pc++;
		address = memory->readByte(pc);
		pc++;
		address |= memory->readByte(pc) << 8;
		m_operationTime = (address & 0xff) + x > 0xff ? 5 : 4;
		a = memory->readByte(address + x);
		updateSzFlags(a);
		pc++;
		break;

	case 0xd8:
		cpuDebug("CLD");
		p &= ~BCD_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0xea:
		cpuDebug("NOP");
		m_operationTime = 2;
		pc++;
		break;

	case 0xf8:
		cpuDebug("SED");
		p |= BCD_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	default:
		m_isUndefinedState = true;
		qDebug("Unknown opcode: 0x%02x", opcode);
	}
}

void Cpu6502::reset()
{
	pc = readWord(0xfffc);
	m_isUndefinedState = false;
}
