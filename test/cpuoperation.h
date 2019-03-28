#ifndef CPUOPERATION_H
#define CPUOPERATION_H

#include <cstdint>

class CpuOperation
{
public:
	explicit CpuOperation(int type, uint16_t address, uint8_t value/*, uint8_t operationTime*/);

	inline bool operator==(const CpuOperation& other) {
		return m_type == other.m_type &&
				m_address == other.m_address &&
				m_value == other.m_value;/* &&
				m_operationTime == other.m_operationTime;*/
	}

	inline bool operator!=(const CpuOperation& other) { return !(*this == other); }

	static const int OPERATION_TYPE_READ = 1;
	static const int OPERATION_TYPE_WRITE = 2;

private:
	int m_type;
	uint16_t m_address;
	uint8_t m_value;
	//uint8_t m_operationTime;
};

#endif // CPUOPERATION_H
