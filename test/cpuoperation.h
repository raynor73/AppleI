#ifndef CPUOPERATION_H
#define CPUOPERATION_H

#include <cstdint>

class CpuOperation
{
public:
	CpuOperation(int type, uint16_t address, uint8_t value/*, uint8_t operationTime*/);

	/*inline bool operator==(const CpuOperation& other) {
		return m_type == other.m_type &&
				m_address == other.m_address &&
				m_value == other.m_value;
	}

	inline bool operator!=(const CpuOperation& other) { return !(*this == other); }*/

	//no match for 'operator==' (operand types are 'const CpuOperation' and 'const CpuOperation')

	inline int type() const { return m_type; }
	inline uint16_t address() const { return m_address; }
	inline uint8_t value() const { return m_value; }

	friend bool operator ==(const CpuOperation& lhs, const CpuOperation& rhs);

	static const int OPERATION_TYPE_READ = 1;
	static const int OPERATION_TYPE_WRITE = 2;

private:
	int m_type;
	uint16_t m_address;
	uint8_t m_value;
	//uint8_t m_operationTime;
};

bool operator ==(const CpuOperation& lhs, const CpuOperation& rhs);
bool operator !=(const CpuOperation& lhs, const CpuOperation& rhs);

#endif // CPUOPERATION_H
