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
	uint8_t value;
	switch (opcode) {
	case 0x01:
		cpuDebug("ORA Indirect X");
		pc++;
		_or(loadIndirectX());
		m_operationTime = 6;
		pc++;
		break;

	case 0x05:
		cpuDebug("ORA Zero Page");
		pc++;
		_or(memory->readByte(memory->readByte(pc)));
		m_operationTime = 3;
		pc++;
		break;

	case 0x06:
		cpuDebug("ASL Zero Page");
		pc++;
		address = memory->readByte(pc);
		memory->writeByte(address, asl(memory->readByte(address)));
		m_operationTime = 5;
		pc++;
		break;

	case 0x08:
		cpuDebug("PHP");
		pushByte(p);
		m_operationTime = 3;
		pc++;
		break;

	case 0x09:
		cpuDebug("ORA Immediate");
		pc++;
		_or(memory->readByte(pc));
		m_operationTime = 2;
		pc++;
		break;

	case 0x0d:
		cpuDebug("ORA Absolute");
		pc++;
		_or(memory->readByte(readWord(pc)));
		m_operationTime = 4;
		pc += 2;
		break;

	case 0x11:
		cpuDebug("ORA Indirect Y");
		pc++;
		_or(loadIndirectY(5, true));
		pc++;
		break;

	case 0x15:
		cpuDebug("ORA Zero Page X");
		pc++;
		_or(memory->readByte((memory->readByte(pc) + x) & 0xff));
		m_operationTime = 4;
		pc++;
		break;

	case 0x16:
		cpuDebug("ASL Zero Page, X");
		pc++;
		address = (memory->readByte(pc) + x) & 0xff;
		memory->writeByte(address, asl(memory->readByte(address)));
		m_operationTime = 6;
		pc++;
		break;

	case 0x0a:
		cpuDebug("ASL Accumulator");
		a = asl(a);
		m_operationTime = 2;
		pc++;
		break;

	case 0x0e:
		cpuDebug("ASL Absolute");
		pc++;
		address = readWord(pc);
		memory->writeByte(address, asl(memory->readByte(address)));
		m_operationTime = 6;
		pc += 2;
		break;

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

	case 0x19:
		cpuDebug("ORA Absolute Y");
		pc++;
		_or(loadAbsoluteY(4, true));
		pc += 2;
		break;

	case 0x1d:
		cpuDebug("ORA Absolute X");
		pc++;
		_or(loadAbsoluteX(4, true));
		pc += 2;
		break;

	case 0x1e:
		cpuDebug("ASL Absolute X");
		pc++;
		address = readWord(pc) + x;
		memory->writeByte(address, asl(memory->readByte(address)));
		m_operationTime = 7;
		pc += 2;
		break;

	case 0x20:
		cpuDebug("JSR");
		pc++;
		pushWord(pc + 1);
		pc = readWord(pc);
		m_operationTime = 6;
		break;

	case 0x21:
		cpuDebug("AND Indirect X");
		pc++;
		_and(loadIndirectX());
		m_operationTime = 6;
		pc++;
		break;

	case 0x24:
		cpuDebug("BIT Zero Page");
		pc++;
		bitTest(memory->readByte(memory->readByte(pc)));
		m_operationTime = 3;
		pc++;
		break;

	case 0x25:
		cpuDebug("AND Zero Page");
		pc++;
		_and(memory->readByte(memory->readByte(pc)));
		m_operationTime = 3;
		pc++;
		break;

	case 0x26:
		cpuDebug("ROL Zero Page");
		pc++;
		address = memory->readByte(pc);
		memory->writeByte(address, rol(memory->readByte(address)));
		m_operationTime = 5;
		pc++;
		break;

	case 0x28:
		cpuDebug("PLP");
		p = popByte();
		m_operationTime = 4;
		pc++;
		break;

	case 0x29:
		cpuDebug("AND Immediate");
		pc++;
		_and(memory->readByte(pc));
		m_operationTime = 2;
		pc++;
		break;

	case 0x2a:
		cpuDebug("ROL Accumulator");
		a = rol(a);
		m_operationTime = 2;
		pc++;
		break;

	case 0x2c:
		cpuDebug("BIT Absolute");
		pc++;
		bitTest(memory->readByte(readWord(pc)));
		m_operationTime = 4;
		pc += 2;
		break;

	case 0x2d:
		cpuDebug("AND Absolute");
		pc++;
		_and(memory->readByte(readWord(pc)));
		m_operationTime = 4;
		pc += 2;
		break;

	case 0x2e:
		cpuDebug("ROL Absolute");
		pc++;
		address = readWord(pc);
		memory->writeByte(address, rol(memory->readByte(address)));
		m_operationTime = 6;
		pc += 2;
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

	case 0x31:
		cpuDebug("AND Indirect Y");
		pc++;
		_and(loadIndirectY(5, true));
		pc++;
		break;

	case 0x35:
		cpuDebug("AND Zero Page X");
		pc++;
		_and(memory->readByte((memory->readByte(pc) + x) & 0xff));
		m_operationTime = 4;
		pc++;
		break;

	case 0x36:
		cpuDebug("ROL Zero Page X");
		pc++;
		address = (memory->readByte(pc) + x) & 0xff;
		memory->writeByte(address, rol(memory->readByte(address)));
		m_operationTime = 6;
		pc++;
		break;

	case 0x38:
		cpuDebug("SEC");
		p |= CARRY_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0x39:
		cpuDebug("AND Absolute Y");
		pc++;
		_and(loadAbsoluteY(4, true));
		pc += 2;
		break;

	case 0x3d:
		cpuDebug("AND Absolute X");
		pc++;
		_and(loadAbsoluteX(4, true));
		pc += 2;
		break;

	case 0x3e:
		cpuDebug("ROL Absolute X");
		pc++;
		address = readWord(pc) + x;
		memory->writeByte(address, rol(memory->readByte(address)));
		m_operationTime = 7;
		pc += 2;
		break;

	case 0x41:
		cpuDebug("EOR Indirect X");
		pc++;
		eor(loadIndirectX());
		m_operationTime = 6;
		pc++;
		break;

	case 0x45:
		cpuDebug("EOR Zero Page");
		pc++;
		eor(memory->readByte(memory->readByte(pc)));
		m_operationTime = 3;
		pc++;
		break;

	case 0x46:
		cpuDebug("LSR Zero Page");
		pc++;
		address = memory->readByte(pc);
		memory->writeByte(address, lsr(memory->readByte(address)));
		m_operationTime = 5;
		pc++;
		break;

	case 0x48:
		cpuDebug("PHA");
		pushByte(a);
		m_operationTime = 3;
		pc++;
		break;

	case 0x49:
		cpuDebug("EOR Immediate");
		pc++;
		eor(memory->readByte(pc));
		m_operationTime = 2;
		pc++;
		break;

	case 0x4a:
		cpuDebug("LSR Accumulator");
		a = lsr(a);
		m_operationTime = 2;
		pc++;
		break;

	case 0x4c:
		cpuDebug("JMP Absolute");
		pc++;
		pc = readWord(pc);
		m_operationTime = 3;
		break;

	case 0x4d:
		cpuDebug("EOR Absolute");
		pc++;
		eor(memory->readByte(readWord(pc)));
		m_operationTime = 4;
		pc += 2;
		break;

	case 0x4e:
		cpuDebug("LSR Absolute");
		pc++;
		address = readWord(pc);
		memory->writeByte(address, lsr(memory->readByte(address)));
		m_operationTime = 6;
		pc += 2;
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

	case 0x51:
		cpuDebug("EOR Indirect Y");
		pc++;
		eor(loadIndirectY(5, true));
		m_operationTime = 6;
		pc++;
		break;

	case 0x55:
		cpuDebug("EOR Zero Page X");
		pc++;
		eor(memory->readByte((memory->readByte(pc) + x) & 0xff));
		m_operationTime = 4;
		pc++;
		break;

	case 0x56:
		cpuDebug("LSR Zero Page X");
		pc++;
		address = (memory->readByte(pc) + x) & 0xff;
		memory->writeByte(address, lsr(memory->readByte(address)));
		m_operationTime = 6;
		pc++;
		break;

	case 0x58:
		cpuDebug("CLI");
		p &= ~INTERRUPT_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0x59:
		cpuDebug("EOR Absolute Y");
		pc++;
		eor(loadAbsoluteY(4, true));
		pc += 2;
		break;

	case 0x5d:
		cpuDebug("EOR Absolute X");
		pc++;
		eor(loadAbsoluteX(4, true));
		pc += 2;
		break;

	case 0x5e:
		cpuDebug("LSR Absolute X");
		pc++;
		address = readWord(pc) + x;
		memory->writeByte(address, lsr(memory->readByte(address)));
		m_operationTime = 7;
		pc += 2;
		break;

	case 0x60:
		cpuDebug("RTS");
		pc = popWord();
		m_operationTime = 6;
		pc++;
		break;

	case 0x61:
		cpuDebug("ADC Indirect X");
		pc++;
		a = adc8(a, loadIndirectX());
		m_operationTime = 6;
		pc++;
		break;

	case 0x65:
		cpuDebug("ADC Zero Page");
		pc++;
		a = adc8(a, memory->readByte(memory->readByte(pc)));
		m_operationTime = 3;
		pc++;
		break;

	case 0x68:
		cpuDebug("PLA");
		a = popByte();
		m_operationTime = 4;
		pc++;
		break;

	case 0x69:
		cpuDebug("ADC Immediate");
		pc++;
		a = adc8(a, memory->readByte(pc));
		m_operationTime = 2;
		pc++;
		break;

	case 0x6c:
		cpuDebug("JMP Indirect");
		pc++;
		address = readWord(pc);
		address2 = memory->readByte(address);
		value = address >> 8;
		address++;
		address &= 0xff;
		address |= value << 8;
		address2 |= memory->readByte(address) << 8;
		pc = address2;
		m_operationTime = 5;
		break;

	case 0x6d:
		cpuDebug("ADC Absolute");
		pc++;
		a = adc8(a, memory->readByte(readWord(pc)));
		m_operationTime = 4;
		pc += 2;
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

	case 0x71:
		cpuDebug("ADC Indirect Y");
		pc++;
		a = adc8(a, loadIndirectY(5, true));
		pc++;
		break;

	case 0x75:
		cpuDebug("ADC Zero Page X");
		pc++;
		a = adc8(a, memory->readByte((memory->readByte(pc) + x) & 0xff));
		m_operationTime = 4;
		pc++;
		break;

	case 0x78:
		cpuDebug("SEI");
		p |= INTERRUPT_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0x79:
		cpuDebug("ADC Absolute Y");
		pc++;
		a = adc8(a, loadAbsoluteY(4, true));
		pc += 2;
		break;

	case 0x7d:
		cpuDebug("ADC Absolute X");
		pc++;
		a = adc8(a, loadAbsoluteX(4, true));
		pc += 2;
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

	case 0x86:
		cpuDebug("STX Zero Page");
		pc++;
		memory->writeByte(memory->readByte(pc), x);
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

	case 0x8e:
		cpuDebug("STX Absolute");
		pc++;
		memory->writeByte(readWord(pc), x);
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

	case 0x96:
		cpuDebug("STX Zero Page Y");
		pc++;
		memory->writeByte((memory->readByte(pc) + y) & 0xff, x);
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

	case 0x9a:
		cpuDebug("TXS");
		sp = x;
		m_operationTime = 2;
		pc++;
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

	case 0xa2:
		cpuDebug("LDX Immediate");
		pc++;
		x = memory->readByte(pc);
		m_operationTime = 2;
		updateSzFlags(x);
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

	case 0xa6:
		cpuDebug("LDX Zero Page");
		pc++;
		x = memory->readByte(memory->readByte(pc));
		m_operationTime = 3;
		updateSzFlags(x);
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

	case 0xae:
		cpuDebug("LDX Absolute");
		pc++;
		x = memory->readByte(readWord(pc));
		m_operationTime = 4;
		updateSzFlags(x);
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

	case 0xb6:
		cpuDebug("LDX Zero Page Y");
		pc++;
		x = memory->readByte((memory->readByte(pc) + y) & 0xff);
		m_operationTime = 4;
		updateSzFlags(x);
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

	case 0xba:
		cpuDebug("TSX");
		x = sp;
		m_operationTime = 2;
		pc++;
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

	case 0xbe:
		cpuDebug("LDX Absolute Y");
		pc++;
		x = loadAbsoluteY(4, true);
		updateSzFlags(x);
		pc += 2;
		break;

	case 0xc0:
		cpuDebug("CPY Immediate");
		pc++;
		sbc(y, memory->readByte(pc), false);
		m_operationTime = 2;
		pc++;
		break;

	case 0xc1:
		cpuDebug("CMP Indirect X");
		pc++;
		sbc(a, loadIndirectX(), false);
		m_operationTime = 6;
		pc++;
		break;

	case 0xc4:
		cpuDebug("CPY Zero Page");
		pc++;
		sbc(y, memory->readByte(memory->readByte(pc)), false);
		m_operationTime = 3;
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

	case 0xcc:
		cpuDebug("CPY Absolute");
		pc++;
		sbc(y, memory->readByte(readWord(pc)), false);
		m_operationTime = 4;
		pc += 2;
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

	case 0xe1:
		cpuDebug("SBC Indirect X");
		pc++;
		a = sbc(a, loadIndirectX(), true);
		m_operationTime = 6;
		pc++;
		break;

	case 0xe5:
		cpuDebug("SBC Zero Page");
		pc++;
		a = sbc(a, memory->readByte(memory->readByte(pc)), true);
		m_operationTime = 3;
		pc++;
		break;

	case 0xe6:
		cpuDebug("INC Zero Page");
		pc++;
		address = memory->readByte(pc);
		value = memory->readByte(address) + 1;
		memory->writeByte(address, value);
		updateSzFlags(value);
		m_operationTime = 5;
		pc++;
		break;

	case 0xe8:
		cpuDebug("INX");
		x++;
		updateSzFlags(x);
		m_operationTime = 2;
		pc++;
		break;

	case 0xe9:
		cpuDebug("SBC Immediate");
		pc++;
		a = sbc(a, memory->readByte(pc), true);
		m_operationTime = 2;
		pc++;
		break;

	case 0xea:
		cpuDebug("NOP");
		m_operationTime = 2;
		pc++;
		break;

	case 0xed:
		cpuDebug("SBC Absolute");
		pc++;
		a = sbc(a, memory->readByte(readWord(pc)), true);
		m_operationTime = 4;
		pc += 2;
		break;

	case 0xee:
		cpuDebug("INC Absolute");
		pc++;
		address = readWord(pc);
		value = memory->readByte(address) + 1;
		memory->writeByte(address, value);
		updateSzFlags(value);
		m_operationTime = 6;
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

	case 0xf1:
		cpuDebug("SBC Indirect Y");
		pc++;
		a = sbc(a, loadIndirectY(5, true), true);
		pc++;
		break;

	case 0xf5:
		cpuDebug("SBC Zero Page X");
		pc++;
		a = sbc(a, memory->readByte((memory->readByte(pc) + x) & 0xff), true);
		m_operationTime = 4;
		pc++;
		break;

	case 0xf6:
		cpuDebug("INC Zero Page X");
		pc++;
		address = (memory->readByte(pc) + x) & 0xff;
		value = memory->readByte(address) + 1;
		memory->writeByte(address, value);
		updateSzFlags(value);
		m_operationTime = 6;
		pc++;
		break;

	case 0xf8:
		cpuDebug("SED");
		p |= BCD_FLAG_MASK;
		m_operationTime = 2;
		pc++;
		break;

	case 0xf9:
		cpuDebug("SBC Absolute Y");
		pc++;
		a = sbc(a, loadAbsoluteY(4, true), true);
		pc += 2;
		break;

	case 0xfd:
		cpuDebug("SBC Absolute X");
		pc++;
		a = sbc(a, loadAbsoluteX(4, true), true);
		pc += 2;
		break;

	case 0xfe:
		cpuDebug("INC Absolute X");
		pc++;
		address = readWord(pc) + x;
		value = memory->readByte(address) + 1;
		memory->writeByte(address, value);
		updateSzFlags(value);
		m_operationTime = 7;
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
	p |= INTERRUPT_FLAG_MASK;
	m_isUndefinedState = false;
}
