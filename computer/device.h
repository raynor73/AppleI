#ifndef DEVICE_H
#define DEVICE_H

#include "cpu6502/cpu6502memory.h"

class Device : public Mos6502::Memory
{
public:
	virtual bool isUsingAddress(const uint16_t address) = 0;
};

#endif // DEVICE_H
