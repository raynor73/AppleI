#include "testcase.h"
#include "m6502.h"
#include "memory.h"

TestCase::TestCase(
		Mos6502::Cpu *cpu,
		TestMemory *testMemory,
		const CpuState initialCpuState,
		const std::map<uint16_t, uint8_t> *initialMemoryState,
		const std::vector<CpuOperation> *expectedOperations
) : m_cpu(cpu),
	m_testMemory(testMemory),
	m_expectedOperations(expectedOperations)
{
	m_cpuStateBuffer[0] = initialCpuState.pc();
	m_cpuStateBuffer[1] = initialCpuState.p();
	m_cpuStateBuffer[2] = initialCpuState.a();
	m_cpuStateBuffer[3] = initialCpuState.x();
	m_cpuStateBuffer[4] = initialCpuState.y();
	m_cpuStateBuffer[5] = initialCpuState.sp();
	loadState(m_cpuStateBuffer);

	cpu->a = initialCpuState.a();
	cpu->x = initialCpuState.x();
	cpu->y = initialCpuState.y();
	cpu->sp = initialCpuState.sp();
	cpu->p = initialCpuState.p();
	cpu->pc = initialCpuState.pc();

	TestMemory &etalonTestMemory = memGetTestMemory();
	for (std::map<uint16_t, uint8_t>::const_iterator it = initialMemoryState->begin(); it != initialMemoryState->end(); it++) {
		testMemory->writeByte(it->first, it->second);
		etalonTestMemory.writeByte(it->first, it->second);
	}
	testMemory->resetOperationsLog();
	etalonTestMemory.resetOperationsLog();
}

void TestCase::performTest()
{
	m_cpu->clockTick();
	step();
}

bool TestCase::passed()
{
	const std::vector<CpuOperation> *actualOperations = m_testMemory->operationsLog();
	if (m_expectedOperations->size() != actualOperations->size()) {
		return false;
	}

	for (uint32_t i = 0; i < actualOperations->size(); i++) {
		if (m_expectedOperations[i] != actualOperations[i]) {
			return false;
		}
	}

	return true;
}

TestCase::~TestCase() {}
