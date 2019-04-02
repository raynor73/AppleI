#include "utils.h"

QString formatCpuState(const Mos6502::Cpu &cpu)
{
	int negativeFlag = (cpu.p & Mos6502::Cpu::NEGATIVE_FLAG_MASK) != 0 ? 1 : 0;
	int overflowFlag = (cpu.p & Mos6502::Cpu::OVERFLOW_FLAG_MASK) != 0 ? 1 : 0;
	int breakpointFlag = (cpu.p & Mos6502::Cpu::BREAKPOINT_FLAG_MASK) != 0 ? 1 : 0;
	int bcdFlag = (cpu.p & Mos6502::Cpu::BCD_FLAG_MASK) != 0 ? 1 : 0;
	int interruptFlag = (cpu.p & Mos6502::Cpu::INTERRUPT_FLAG_MASK) != 0 ? 1 : 0;
	int zeroFlag = (cpu.p & Mos6502::Cpu::ZERO_FLAG_MASK) != 0 ? 1 : 0;
	int carryFlag = (cpu.p & Mos6502::Cpu::CARRY_FLAG_MASK) != 0 ? 1 : 0;
	return QString(" A: 0x  %1\n X: 0x  %2\n Y: 0x  %3\nSP: 0x%4\nPC: 0x%5\nFlags: N:%6 V:%7 B:%8 D:%9 I:%10 Z:%11 C:%12")
			.arg(cpu.a, 2, 16, QLatin1Char('0'))
			.arg(cpu.x, 2, 16, QLatin1Char('0'))
			.arg(cpu.y, 2, 16, QLatin1Char('0'))
			.arg(cpu.sp, 4, 16, QLatin1Char('0'))
			.arg(cpu.pc, 4, 16, QLatin1Char('0'))
			.arg(negativeFlag)
			.arg(overflowFlag)
			.arg(breakpointFlag)
			.arg(bcdFlag)
			.arg(interruptFlag)
			.arg(zeroFlag)
			.arg(carryFlag);
}
