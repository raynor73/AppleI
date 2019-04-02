#include "testcase.h"
#include "m6502.h"

TestCase::TestCase(
		Mos6502::Cpu *cpu,
		const CpuState *initialCpuState,
		const std::map<uint16_t, uint8_t> *initialMemoryState,
		const std::map<uint16_t, uint8_t> *expectedMemoryState,
		const CpuState *expectedCpuState
) {
	m_cpuStateBuffer[0] = initialCpuState->pc();
	m_cpuStateBuffer[1] = initialCpuState->p();
	m_cpuStateBuffer[2] = initialCpuState->a();
	m_cpuStateBuffer[3] = initialCpuState->x();
	m_cpuStateBuffer[4] = initialCpuState->y();
	m_cpuStateBuffer[5] = initialCpuState->sp();
}

bool TestCase::passed()
{
	return false;
}

TestCase::~TestCase() {}
