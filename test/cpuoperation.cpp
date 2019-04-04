#include "cpuoperation.h"

CpuOperation::CpuOperation(int type, uint16_t address, uint8_t value/*, uint8_t operationTime*/) :
	m_type(type),
	m_address(address),
	m_value(value)/*,
	m_operationTime(operationTime)*/
{}

bool operator ==(const CpuOperation& lhs, const CpuOperation& rhs) {
	return lhs.m_type == rhs.m_type &&
			lhs.m_address == rhs.m_address &&
			lhs.m_value == rhs.m_value;
}

bool operator !=(const CpuOperation &lhs, const CpuOperation &rhs)
{
	return !(lhs == rhs);
}
