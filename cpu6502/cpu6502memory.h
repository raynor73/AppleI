#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>

namespace Mos6502 {

class Memory
{
public:
	virtual uint8_t readByte(const uint16_t address) = 0;
	virtual void writeByte(const uint16_t address, const uint8_t value) = 0;

	virtual ~Memory();
};

}


#endif // MEMORY_H
