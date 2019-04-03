#ifndef CPUSTATE_H
#define CPUSTATE_H

#include <cstdint>

class CpuState
{
public:
	CpuState();

	CpuState(const uint8_t a, const uint8_t x, const uint8_t y, const uint8_t m_sp, const uint16_t pc, const uint8_t p);

	inline bool operator==(const CpuState& other) {
		return m_a == other.m_a &&
				m_x == other.m_x &&
				m_y == other.m_y &&
				m_sp == other.m_sp &&
				m_pc == other.m_pc &&
				m_p == other.m_p;
	}

	inline bool operator!=(const CpuState& other) { return !(*this == other); }

	inline uint8_t a() const { return m_a; }
	inline uint8_t x() const { return m_x; }
	inline uint8_t y() const { return m_y; }
	inline uint8_t sp() const { return m_sp; }
	inline uint16_t pc() const { return m_pc; }
	inline uint8_t p() const { return m_p; }

private:
	uint8_t m_a;
	uint8_t m_x;
	uint8_t m_y;
	uint8_t m_sp;
	uint16_t m_pc;
	uint8_t m_p;
};

#endif // CPUSTATE_H
