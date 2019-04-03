#include "testmemory.h"

uint8_t TestMemory::readByte(const uint16_t address)
{
	uint8_t value = m_memoryBytes[address];
	m_operationsLog.push_back(CpuOperation(CpuOperation::OPERATION_TYPE_READ, address, value));
	return value;
}

void TestMemory::writeByte(const uint16_t address, const uint8_t value)
{
	m_operationsLog.push_back(CpuOperation(CpuOperation::OPERATION_TYPE_WRITE, address, value));
	m_memoryBytes[address] = value;
}

void TestMemory::resetOperationsLog()
{
	m_operationsLog.clear();
}
