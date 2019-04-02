#ifndef TESTMEMORY_H
#define TESTMEMORY_H

#include "cpu6502/cpu6502memory.h"

class TestMemory : public Mos6502::Memory
{
public:
	virtual uint8_t readByte(const uint16_t address) override;
	virtual void writeByte(const uint16_t address, const uint8_t value) override;
};

#endif // TESTMEMORY_H
