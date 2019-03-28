#include "cpuoperation.h"

CpuOperation::CpuOperation(int type, uint16_t address, uint8_t value/*, uint8_t operationTime*/) :
	m_type(type),
	m_address(address),
	m_value(value)/*,
	m_operationTime(operationTime)*/
{}
