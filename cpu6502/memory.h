#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

class Memory
{
public:
	virtual uint8_t readByte(const uint16_t address) = 0;
	virtual void writeByte(const uint16_t address, const uint8_t value) = 0;

	virtual ~Memory() = 0;
};

#endif // MEMORY_H
