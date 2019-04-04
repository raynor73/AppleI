#ifndef TESTCASE_H
#define TESTCASE_H

#include <map>
#include <vector>
#include "cpu6502/cpu6502.h"
#include "cpustate.h"
#include "testmemory.h"

class TestCase
{
public:
	TestCase(
			Mos6502::Cpu *cpu,
			TestMemory *testMemory,
			const CpuState initialCpuState,
			const std::map<uint16_t, uint8_t> *initialMemoryState
	);

	TestCase(const TestCase &other) = delete;
	TestCase(TestCase &&other) = delete;

	void performTest();

	bool passed();

	virtual ~TestCase();

protected:
	int m_cpuStateBuffer[6];
	Mos6502::Cpu *m_cpu;
	TestMemory *m_testMemory;
	const std::vector<CpuOperation> *m_expectedOperations;
	CpuState m_expectedCpuState;

private:
	void printExpectedCpuState() const;
	void printActualCpuState() const;
	void printMemoryOperations(const std::vector<CpuOperation> &operations) const;
};

#endif // TESTCASE_H
