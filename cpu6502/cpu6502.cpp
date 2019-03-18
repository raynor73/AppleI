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
	switch (opcode) {
	case 0x10:
		cpuDebug("BPL");
		pc++;
		if ((p & NEGATIVE_FLAG_MASK) == 0)
		{
			branch();
		}
		else
		{
			m_operationTime = 2;
		}
		pc++;
		break;

	case 0x18:
		cpuDebug("CLC");
		p &= ~CARRY_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0x20:
		cpuDebug("JSR");
		pc++;
		pushWord(pc + 1);
		pc = readWord(pc);
		m_operationTime = 6;
		break;

	case 0x30:
		cpuDebug("BMI");
		pc++;
		if ((p & NEGATIVE_FLAG_MASK) != 0)
		{
			branch();
		}
		else
		{
			m_operationTime = 2;
		}
		pc++;
		break;

	case 0x38:
		cpuDebug("SEC");
		p |= CARRY_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0x50:
		cpuDebug("BVC");
		pc++;
		if ((p & OVERFLOW_FLAG_MASK) == 0)
		{
			branch();
		}
		else
		{
			m_operationTime = 2;
		}
		pc++;
		break;

	case 0x58:
		cpuDebug("CLI");
		p &= ~INTERRUPT_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0x70:
		cpuDebug("BVS");
		pc++;
		if ((p & OVERFLOW_FLAG_MASK) != 0)
		{
			branch();
		}
		else
		{
			m_operationTime = 2;
		}
		pc++;
		break;

	case 0x78:
		cpuDebug("SEI");
		p |= INTERRUPT_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0x81:
		cpuDebug("STA Indirect X");
		pc++;
		storeIndirectX(a);
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

	case 0x88:
		cpuDebug("DEY");
		y--;
		updateSzFlags(y);
		m_operationTime = 2;
		pc++;
		break;

	case 0x8a:
		cpuDebug("TXA");
		a = x;
		updateSzFlags(a);
		m_operationTime = 2;
		pc++;
		break;

	case 0x8c:
		cpuDebug("STY Absolute");
		pc++;
		memory->writeByte(readWord(pc), y);
		m_operationTime = 4;
		pc += 2;
		break;

	case 0x8d:
		cpuDebug("STA Absolute");
		pc++;
		memory->writeByte(readWord(pc), a);
		m_operationTime = 4;
		pc += 2;
		break;

	case 0x90:
		cpuDebug("BCC");
		pc++;
		if ((p & CARRY_FLAG_MASK) == 0)
		{
			branch();
		}
		else
		{
			m_operationTime = 2;
		}
		pc++;
		break;

	case 0x91:
		cpuDebug("STA Indirect Indexed");
		pc++;
		storeIndirectY(a);
		m_operationTime = 6;
		pc++;
		break;

	case 0x94:
		cpuDebug("STY Zero Page X");
		pc++;
		memory->writeByte((memory->readByte(pc) + x) & 0xff, y);
		m_operationTime = 4;
		pc++;
		break;

	case 0x95:
		cpuDebug("STA Zero Page X");
		pc++;
		memory->writeByte((memory->readByte(pc) + x) & 0xff, a);
		m_operationTime = 4;
		pc++;
		break;

	case 0x98:
		cpuDebug("TYA");
		a = y;
		updateSzFlags(a);
		m_operationTime = 2;
		pc++;
		break;

	case 0x99:
		cpuDebug("STA Absolute Y");
		pc++;
		memory->writeByte(readWord(pc) + y, a);
		m_operationTime = 5;
		pc += 2;
		break;

	case 0x9d:
		cpuDebug("STA Absolute X");
		pc++;
		memory->writeByte(readWord(pc) + x, a);
		m_operationTime = 5;
		pc += 2;
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
		cpuDebug("LDA Indirect X");
		pc++;
		a = loadIndirectX();
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

	case 0xa5:
		cpuDebug("LDA Zero Page");
		pc++;
		a = memory->readByte(memory->readByte(pc));
		m_operationTime = 3;
		updateSzFlags(a);
		pc++;
		break;

	case 0xa8:
		cpuDebug("TAY");
		y = a;
		updateSzFlags(y);
		m_operationTime = 2;
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

	case 0xaa:
		cpuDebug("TAX");
		x = a;
		updateSzFlags(x);
		m_operationTime = 2;
		pc++;
		break;

	case 0xac:
		cpuDebug("LDY Absolute");
		pc++;
		y = memory->readByte(readWord(pc));
		m_operationTime = 4;
		updateSzFlags(y);
		pc += 2;
		break;

	case 0xad:
		cpuDebug("LDA Absolute");
		pc++;
		a = memory->readByte(readWord(pc));
		m_operationTime = 4;
		updateSzFlags(a);
		pc += 2;
		break;

	case 0xb0:
		cpuDebug("BCS");
		pc++;
		if ((p & CARRY_FLAG_MASK) != 0)
		{
			branch();
		}
		else
		{
			m_operationTime = 2;
		}
		pc++;
		break;

	case 0xb1:
		cpuDebug("LDA Indirect Y");
		pc++;
		a = loadIndirectY(5, true);
		updateSzFlags(a);
		pc++;
		break;

	case 0xb4:
		cpuDebug("LDY Zero Page X");
		pc++;
		y = memory->readByte((memory->readByte(pc) + x) & 0xff);
		m_operationTime = 4;
		updateSzFlags(y);
		pc++;
		break;

	case 0xb5:
		cpuDebug("LDA Zero Page X");
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
		cpuDebug("LDA Absolute Y");
		pc++;
		a = loadAbsoluteY(4, true);
		updateSzFlags(a);
		pc += 2;
		break;

	case 0xbc:
		cpuDebug("LDY Absolute X");
		pc++;
		y = loadAbsoluteX(4, true);
		updateSzFlags(y);
		pc += 2;
		break;

	case 0xbd:
		cpuDebug("LDA Absolute X");
		pc++;
		a = loadAbsoluteX(4, true);
		updateSzFlags(a);
		pc += 2;
		break;

	case 0xc1:
		cpuDebug("CMP Indirect X");
		pc++;
		sbc(a, loadIndirectX(), false);
		m_operationTime = 6;
		pc++;
		break;

	case 0xc5:
		cpuDebug("CMP Zero Page");
		pc++;
		sbc(a, memory->readByte(memory->readByte(pc)), false);
		m_operationTime = 3;
		pc++;
		break;

	case 0xc8:
		cpuDebug("INY");
		y++;
		updateSzFlags(y);
		m_operationTime = 2;
		pc++;
		break;

	case 0xc9:
		cpuDebug("CMP Immediate");
		pc++;
		sbc(a, memory->readByte(pc), false);
		m_operationTime = 2;
		pc++;
		break;

	case 0xca:
		cpuDebug("DEX");
		x--;
		updateSzFlags(x);
		m_operationTime = 2;
		pc++;
		break;

	case 0xcd:
		cpuDebug("CMP Absolute");
		pc++;
		sbc(a, memory->readByte(readWord(pc)), false);
		m_operationTime = 4;
		pc += 2;
		break;

	case 0xd0:
		cpuDebug("BNE");
		pc++;
		if ((p & ZERO_FLAG_MASK) == 0)
		{
			branch();
		}
		else
		{
			m_operationTime = 2;
		}
		pc++;
		break;

	case 0xd1:
		cpuDebug("CPM Indirect Y");
		pc++;
		sbc(a, loadIndirectY(5, true), false);
		pc++;
		break;

	case 0xd5:
		cpuDebug("CMP Zero Page X");
		pc++;
		sbc(a, memory->readByte((memory->readByte(pc) + x) & 0xff), false);
		m_operationTime = 4;
		pc++;
		break;

	case 0xd8:
		cpuDebug("CLD");
		p &= ~BCD_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0xd9:
		cpuDebug("CMP Absolute Y");
		pc++;
		sbc(a, loadAbsoluteY(4, true), false);
		pc += 2;
		break;

	case 0xdd:
		cpuDebug("CMP Absolute X");
		pc++;
		sbc(a, loadAbsoluteX(4, true), false);
		pc += 2;
		break;

	case 0xe8:
		cpuDebug("INX");
		x++;
		updateSzFlags(x);
		m_operationTime = 2;
		pc++;
		break;

	case 0xea:
		cpuDebug("NOP");
		m_operationTime = 2;
		pc++;
		break;

	case 0xf0:
		cpuDebug("BEQ");
		pc++;
		if ((p & ZERO_FLAG_MASK) != 0)
		{
			branch();
		}
		else
		{
			m_operationTime = 2;
		}
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
