#include "cpu6502.h"

Cpu6502::Cpu6502()
{

}

void Cpu6502::clockTick()
{
	if ((memory->readByte(0xd011) & 0x80) != 0) {
		memory->writeByte(0xd012, memory->readByte(0xd010));
	}
}

void Cpu6502::reset()
{

}
