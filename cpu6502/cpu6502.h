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

	inline uint8_t adc8(const uint8_t arg1, const uint8_t arg2)
	{
		if ((p & BCD_FLAG_MASK) == 0)
		{
			uint16_t carry = (p & CARRY_FLAG_MASK) != 0 ? 1 : 0;
			uint16_t result = arg1 + arg2 + carry;

			updateSzFlags(uint8_t(result));

			if (result > 255) {
				p |= CARRY_FLAG_MASK;
			} else {
				p &= ~CARRY_FLAG_MASK;
			}

			bool isFirstArgPositive = (arg1 & 0x80) == 0;
			bool isSecondArgPositive = (arg2 & 0x80) == 0;
			bool isResultPositive = (p & NEGATIVE_FLAG_MASK) == 0;
			if (isFirstArgPositive && isSecondArgPositive && !isResultPositive) {
				p |= OVERFLOW_FLAG_MASK;
			} else if (!isFirstArgPositive && !isSecondArgPositive && isResultPositive) {
				p |= OVERFLOW_FLAG_MASK;
			} else {
				p &= ~OVERFLOW_FLAG_MASK;
			}

			return uint8_t(result);
		}
		else
		{
			uint16_t carry = (p & CARRY_FLAG_MASK) != 0 ? 1 : 0;
			uint16_t binResult = arg1 + arg2 + carry;
			uint16_t intermediateResult;
			uint16_t decResult;
			int16_t signedDecResult;

			if (uint8_t(binResult) == 0)
			{
				p |= ZERO_FLAG_MASK;
			}
			else
			{
				p &= ~ZERO_FLAG_MASK;
			}

			intermediateResult = (arg1 & 0x0f) + (arg2 & 0x0f) + carry;
			if (intermediateResult >= 0x0a)
			{
				intermediateResult = ((intermediateResult + 0x06) & 0x0f) + 0x10;
			}
			decResult = (arg1 & 0xf0) + (arg2 & 0xf0) + intermediateResult;
			if (decResult >= 0xa0)
			{
				decResult += 0x60;
			}
			if (decResult >= 0x100)
			{
				p |= CARRY_FLAG_MASK;
			}
			else
			{
				p &= ~CARRY_FLAG_MASK;
			}

			signedDecResult = (int8_t(arg1) & 0xf0) + (int8_t(arg2) & 0xf0) + int16_t(intermediateResult);
			if ((signedDecResult & 0x80) != 0)
			{
				p |= NEGATIVE_FLAG_MASK;
			}
			else
			{
				p &= ~NEGATIVE_FLAG_MASK;
			}
			if (signedDecResult < -128 || signedDecResult > 127)
			{
				p |= OVERFLOW_FLAG_MASK;
			}
			else
			{
				p &= ~OVERFLOW_FLAG_MASK;
			}

			return uint8_t(decResult);
		}
	}

	inline uint8_t sbc(const uint8_t arg1, const uint8_t arg2, const bool shouldUpdateOverflowFlag)
	{
		if ((p & BCD_FLAG_MASK) == 0)
		{
			uint16_t borrow = (p & CARRY_FLAG_MASK) != 0 ? 0 : 1;
			uint16_t arg2WithBorrow = arg2 + borrow;
			uint16_t result = arg1 - arg2WithBorrow;

			updateSzFlags(uint8_t(result));

			if (arg1 < arg2WithBorrow) {
				p &= ~CARRY_FLAG_MASK;
			} else {
				p |= CARRY_FLAG_MASK;
			}

			if (shouldUpdateOverflowFlag)
			{
				bool isFirstArgPositive = (arg1 & NEGATIVE_FLAG_MASK) == 0;
				bool isSecondArgPositive = (arg2 & NEGATIVE_FLAG_MASK) == 0;
				bool isResultPositive = (p & NEGATIVE_FLAG_MASK) == 0;
				if (isFirstArgPositive && !isSecondArgPositive && !isResultPositive) {
					p |= OVERFLOW_FLAG_MASK;
				} else if (!isFirstArgPositive && isSecondArgPositive && isResultPositive) {
					p |= OVERFLOW_FLAG_MASK;
				} else {
					p &= ~OVERFLOW_FLAG_MASK;
				}
			}

			return uint8_t(result);
		}
		else
		{
			uint16_t borrow = (p & CARRY_FLAG_MASK) != 0 ? 0 : 1;
			uint16_t arg2WithBorrow = arg2 + borrow;
			uint16_t binResult = arg1 - arg2WithBorrow;
			int16_t decResult;
			int16_t intermediateResult;

			intermediateResult = (int8_t(arg1) & 0x0f) - (int8_t(arg2) & 0x0f) - int8_t(borrow);
			if (intermediateResult < 0)
			{
				intermediateResult = ((intermediateResult - 0x06) & 0x0f) - 0x10;
			}
			decResult = (int8_t(arg1) & 0xf0) - (int8_t(arg2) & 0xf0) + intermediateResult;
			if (decResult < 0)
			{
				decResult -= 0x60;
			}

			updateSzFlags(uint8_t(binResult));

			if (arg1 < arg2WithBorrow) {
				p &= ~CARRY_FLAG_MASK;
			} else {
				p |= CARRY_FLAG_MASK;
			}

			if (shouldUpdateOverflowFlag)
			{
				bool isFirstArgPositive = (arg1 & NEGATIVE_FLAG_MASK) == 0;
				bool isSecondArgPositive = (arg2 & NEGATIVE_FLAG_MASK) == 0;
				bool isResultPositive = (p & NEGATIVE_FLAG_MASK) == 0;
				if (isFirstArgPositive && !isSecondArgPositive && !isResultPositive) {
					p |= OVERFLOW_FLAG_MASK;
				} else if (!isFirstArgPositive && isSecondArgPositive && isResultPositive) {
					p |= OVERFLOW_FLAG_MASK;
				} else {
					p &= ~OVERFLOW_FLAG_MASK;
				}
			}

			return uint8_t(decResult);
		}
	}

	inline void branch()
	{
		uint16_t address = uint16_t(pc + int8_t(memory->readByte(pc)));
		if (((pc + 1) & 0xff00) == (address & 0xff00))
		{
			m_operationTime = 3;
		}
		else {
			m_operationTime = 4;
		}
		pc = address;
	}

	inline void pushByte(const uint8_t value)
	{
		memory->writeByte(sp | STACK_PAGE, value);
		sp++;
	}

	inline uint8_t popByte()
	{
		sp--;
		return memory->readByte(sp | STACK_PAGE);
	}

	inline void pushWord(const uint16_t value)
	{
		pushByte(value >> 8);
		pushByte(uint8_t(value));
	}

	inline uint16_t popWord()
	{
		uint16_t value;
		value = popByte();
		value |= popByte() << 8;
		return value;
	}

	inline void bitTest(const uint8_t value)
	{
		if ((value & a) == 0)
		{
			p |= ZERO_FLAG_MASK;
		}
		else
		{
			p &= ~ZERO_FLAG_MASK;
		}

		if ((value & 0x80) != 0)
		{
			p |= NEGATIVE_FLAG_MASK;
		}
		else
		{
			p &= ~NEGATIVE_FLAG_MASK;
		}

		if ((value & 0x40) != 0)
		{
			p |= OVERFLOW_FLAG_MASK;
		}
		else
		{
			p &= ~OVERFLOW_FLAG_MASK;
		}
	}

	static const uint16_t STACK_PAGE = 0x0100;
};

#endif // CPU6502_H
