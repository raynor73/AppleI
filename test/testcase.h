#ifndef TESTCASE_H
#define TESTCASE_H

#include <map>
#include "cpu6502/cpu6502.h"
#include "cpustate.h"

class TestCase
{
public:
	explicit TestCase(
			Mos6502::Cpu *cpu,
			const CpuState *initialCpuState,
			const std::map<uint16_t, uint8_t> *initialMemoryState,
			const std::map<uint16_t, uint8_t> *expectedMemoryState,
			const CpuState *expectedCpuState
	);

	virtual void performTest() = 0;

	bool passed();

	virtual ~TestCase();

private:
	int m_cpuStateBuffer[6];
};

#endif // TESTCASE_H
