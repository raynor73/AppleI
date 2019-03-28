#ifndef TESTCASE_H
#define TESTCASE_H

#include <map>
#include "cpu6502/cpu6502.h"
#include "cpustate.h"

class TestCase
{
public:
	explicit TestCase(
			Cpu6502 *cpu,
			const CpuState *initialCpuState,
			const std::map<uint16_t, uint8_t> *initialMemoryState,
			const std::map<uint16_t, uint8_t> *expectedMemoryState,
			const CpuState *expectedCpuState
	);

	virtual void performTest() = 0;

	bool passed();

	virtual ~TestCase();
};

#endif // TESTCASE_H
