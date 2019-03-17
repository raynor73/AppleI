#ifndef CPU6502_H
#define CPU6502_H

#include <cstdint>
#include "memory.h"

class Cpu6502
{
public:
	Cpu6502();

	uint8_t a;
	uint8_t x;
	uint8_t y;
	uint8_t sp;
	uint16_t pc;
	uint8_t p;

	Memory *memory;

	static const uint8_t NEGATIVE_FLAG_MASK =   0b10000000;
	static const uint8_t OVERFLOW_FLAG_MASK =   0b01000000;
	static const uint8_t BREAKPOINT_FLAG_MASK = 0b00010000;
	static const uint8_t BCD_FLAG_MASK =        0b00001000;
	static const uint8_t INTERRUPT_FLAG_MASK =  0b00000100;
	static const uint8_t ZERO_FLAG_MASK =       0b00000010;
	static const uint8_t CARRY_FLAG_MASK =      0b00000001;
};

#endif // CPU6502_H
