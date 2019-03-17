#ifndef DEVICE_H
#define DEVICE_H

#include "cpu6502/memory.h"

class Device : public Memory
{
public:
	virtual bool isUsingAddress(const uint16_t address) = 0;
};

#endif // DEVICE_H
