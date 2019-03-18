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

	inline uint16_t readWord(const uint16_t address) {
		uint8_t l = memory->readByte(address);
		uint8_t h = memory->readByte(address + 1);
		return (h << 8) | l;
	}

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

	inline void storeIndexedIndirect(const uint8_t value)
	{
		m_address = (memory->readByte(pc) + x) & 0xff;
		m_address2 = memory->readByte(address);
		m_address2 |= memory->readByte(address + 1) << 8;
		memory->writeByte(address2, value);
	}

	inline uint8_t loadIndexedIndirect()
	{
		m_address = (memory->readByte(pc) + x) & 0xff;
		m_address2 = memory->readByte(m_address);
		m_address2 |= memory->readByte(m_address + 1) << 8;
		return memory->readByte(m_address2);
	}

	inline uint8_t loadIndirectIndexed(const uint8_t baseTime, const bool shouldIncrementTimeOnPageCross)
	{
		m_address = memory->readByte(pc);
		m_address2 = memory->readByte(m_address);
		m_address2 |= memory->readByte((m_address + 1) & 0xff) << 8;
		//m_operationTime = (m_address2 & 0xff) + y > 0xff ? 6 : 5;
		a = memory->readByte(m_address2 + y);
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
