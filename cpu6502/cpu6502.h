#ifndef CPU6502_H
#define CPU6502_H

#include <cstdint>
#include "memory.h"

class Cpu6502
{
public:
	uint8_t a;
	uint8_t x;
	uint8_t y;
	uint8_t sp;
	uint16_t pc;
	uint8_t p;

	Memory *memory;

	explicit Cpu6502();

	void clockTick();
	void reset();

	static const uint8_t NEGATIVE_FLAG_MASK =   0b10000000;
	static const uint8_t OVERFLOW_FLAG_MASK =   0b01000000;
	static const uint8_t BREAKPOINT_FLAG_MASK = 0b00010000;
	static const uint8_t BCD_FLAG_MASK =        0b00001000;
	static const uint8_t INTERRUPT_FLAG_MASK =  0b00000100;
	static const uint8_t ZERO_FLAG_MASK =       0b00000010;
	static const uint8_t CARRY_FLAG_MASK =      0b00000001;

private:
	uint8_t m_operationTime;
	bool m_isUndefinedState;

	inline void updateSzFlags(const uint8_t value)
	{
		if ((value & 0x80) != 0)
		{
			p |= NEGATIVE_FLAG_MASK;
		}
		else
		{
			p &= ~NEGATIVE_FLAG_MASK;
		}

		if (value == 0)
		{
			p |= ZERO_FLAG_MASK;
		}
		else
		{
			p &= ~ZERO_FLAG_MASK;
		}
	}

	inline void storeIndirectX(const uint8_t value)
	{
		memory->writeByte(readWordFromZeroPage(memory->readByte(pc) + x), value);
	}

	inline uint8_t loadIndirectX()
	{
		return memory->readByte(readWordFromZeroPage(memory->readByte(pc) + x));
	}

	inline void storeIndirectY(const uint8_t value)
	{
		memory->writeByte(readWordFromZeroPage(memory->readByte(pc)) + y, value);
	}

	inline uint8_t loadIndirectY(const uint8_t baseTime, const bool shouldIncrementTimeOnPageCross)
	{
		uint16_t address = readWordFromZeroPage(memory->readByte(pc));
		if (shouldIncrementTimeOnPageCross)
		{
			m_operationTime = (address & 0xff) + y > 0xff ? (baseTime + 1) : baseTime;
		}
		else
		{
			m_operationTime = baseTime;
		}
		return  memory->readByte(address + y);
	}

	inline uint8_t loadAbsoluteX(const uint8_t baseTime, const bool shouldIncrementTimeOnPageCross)
	{
		uint16_t address = readWord(pc);
		if (shouldIncrementTimeOnPageCross)
		{
			m_operationTime = (address & 0xff) + x > 0xff ? (baseTime + 1) : baseTime;
		}
		else
		{
			m_operationTime = baseTime;
		}
		return  memory->readByte(address + x);
	}

	inline uint8_t loadAbsoluteY(const uint8_t baseTime, const bool shouldIncrementTimeOnPageCross)
	{
		uint16_t address = readWord(pc);
		if (shouldIncrementTimeOnPageCross)
		{
			m_operationTime = (address & 0xff) + y > 0xff ? (baseTime + 1) : baseTime;
		}
		else
		{
			m_operationTime = baseTime;
		}
		return  memory->readByte(address + y);
	}

	inline uint16_t readWord(const uint16_t address)
	{
		uint16_t result;
		result = memory->readByte(address);
		result |= memory->readByte(address + 1) << 8;
		return result;
	}

	inline uint16_t readWordFromZeroPage(const uint8_t address)
	{
		uint16_t result;
		result = memory->readByte(address);
		result |= memory->readByte((address + 1) & 0xff) << 8;
		return result;
	}
};

#endif // CPU6502_H
