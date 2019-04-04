#include <QDebug>
#include <stdlib.h>
#include "testcase.h"
#include "m6502.h"
#include "memory.h"
#include "utils/utils.h"

TestCase::TestCase(
		Mos6502::Cpu *cpu,
		TestMemory *testMemory,
		const CpuState initialCpuState,
		const std::map<uint16_t, uint8_t> *initialMemoryState
) : m_cpu(cpu), m_testMemory(testMemory) {
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
	const std::vector<CpuOperation> *expectedOperations = memGetTestMemory().operationsLog();

	if (expectedOperations->size() != actualOperations->size()) {
		qDebug(
					"Expected number of operations: %d, actual number of operations: %d",
					expectedOperations->size(),
					actualOperations->size()
		);
		printExpectedCpuState();
		printActualCpuState();
		qDebug("Expected memory operations");
		printMemoryOperations(*expectedOperations);
		qDebug("Actual memory operations");
		printMemoryOperations(*actualOperations);
		return false;
	}

	for (uint32_t i = 0; i < actualOperations->size(); i++) {
		if (expectedOperations[i] != actualOperations[i]) {
			qDebug("Memory operations mismatch");
			printExpectedCpuState();
			printActualCpuState();
			qDebug("Expected memory operations");
			printMemoryOperations(*expectedOperations);
			qDebug("Actual memory operations");
			printMemoryOperations(*actualOperations);
			return false;
		}
	}

	int *cpuStateBuffer = dumpState();
	uint16_t pc = cpuStateBuffer[0];
	uint8_t p = cpuStateBuffer[1];
	uint8_t a = cpuStateBuffer[2];
	uint8_t x = cpuStateBuffer[3];
	uint8_t y = cpuStateBuffer[4];
	uint8_t sp = cpuStateBuffer[5];
	free(cpuStateBuffer);
	if (pc != m_cpu->pc || p != m_cpu->p || a != m_cpu->a || x != m_cpu->x || y != m_cpu->y || sp != m_cpu->sp) {
		qDebug("CPU states mismatch");
		printExpectedCpuState();
		printActualCpuState();
		qDebug("Expected memory operations");
		printMemoryOperations(*expectedOperations);
		qDebug("Actual memory operations");
		printMemoryOperations(*actualOperations);
		return false;
	}

	return true;
}

TestCase::~TestCase() {}

void TestCase::printExpectedCpuState() const
{
	int *cpuStateBuffer = dumpState();
	uint16_t pc = cpuStateBuffer[0];
	uint8_t p = cpuStateBuffer[1];
	uint8_t a = cpuStateBuffer[2];
	uint8_t x = cpuStateBuffer[3];
	uint8_t y = cpuStateBuffer[4];
	uint8_t sp = cpuStateBuffer[5];
	free(cpuStateBuffer);

	int negativeFlag = (p & Mos6502::Cpu::NEGATIVE_FLAG_MASK) != 0 ? 1 : 0;
	int overflowFlag = (p & Mos6502::Cpu::OVERFLOW_FLAG_MASK) != 0 ? 1 : 0;
	int breakpointFlag = (p & Mos6502::Cpu::BREAKPOINT_FLAG_MASK) != 0 ? 1 : 0;
	int bcdFlag = (p & Mos6502::Cpu::BCD_FLAG_MASK) != 0 ? 1 : 0;
	int interruptFlag = (p & Mos6502::Cpu::INTERRUPT_FLAG_MASK) != 0 ? 1 : 0;
	int zeroFlag = (p & Mos6502::Cpu::ZERO_FLAG_MASK) != 0 ? 1 : 0;
	int carryFlag = (p & Mos6502::Cpu::CARRY_FLAG_MASK) != 0 ? 1 : 0;
	QString cpuStateString = QString(" A: 0x  %1\n X: 0x  %2\n Y: 0x  %3\nSP: 0x%4\nPC: 0x%5\nFlags: N:%6 V:%7 B:%8 D:%9 I:%10 Z:%11 C:%12")
			.arg(a, 2, 16, QLatin1Char('0'))
			.arg(x, 2, 16, QLatin1Char('0'))
			.arg(y, 2, 16, QLatin1Char('0'))
			.arg(sp, 4, 16, QLatin1Char('0'))
			.arg(pc, 4, 16, QLatin1Char('0'))
			.arg(negativeFlag)
			.arg(overflowFlag)
			.arg(breakpointFlag)
			.arg(bcdFlag)
			.arg(interruptFlag)
			.arg(zeroFlag)
			.arg(carryFlag);
	qDebug("Expected CPU state");
	qDebug(cpuStateString.toLatin1().data());
	qDebug("===");
}

void TestCase::printActualCpuState() const
{
	qDebug("Actual CPU state");
	qDebug(formatCpuState(*m_cpu).toLatin1().data());
	qDebug("===");
}

void TestCase::printMemoryOperations(const std::vector<CpuOperation> &operations) const
{
	for (std::vector<CpuOperation>::const_iterator it = operations.begin(); it != operations.end(); it++) {
		int foobar = CpuOperation::OPERATION_TYPE_READ;
		qDebug(
					"Memory operation: %s; 0x%04x: 0x%02x",
					it->type() == foobar ? "READ" : "WRITE",
					it->address(),
					it->value()
		);
	}
}
