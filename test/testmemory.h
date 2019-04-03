#ifndef TESTMEMORY_H
#define TESTMEMORY_H

#include <vector>
#include "cpu6502/cpu6502memory.h"
#include "cpuoperation.h"

class TestMemory : public Mos6502::Memory
{
public:
	virtual uint8_t readByte(const uint16_t address) override;
	virtual void writeByte(const uint16_t address, const uint8_t value) override;

	void resetOperationsLog();
	inline const std::vector<CpuOperation> *operationsLog() const { return &m_operationsLog; }

private:
	uint8_t m_memoryBytes[0x10000];
	std::vector<CpuOperation> m_operationsLog;
};

#endif // TESTMEMORY_H
