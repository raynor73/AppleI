#include "cpustate.h"


CpuState::CpuState() : m_a(0), m_x(0), m_y(0), m_sp(0), m_pc(0), m_p(0) {}

CpuState::CpuState(
		const uint8_t a,
		const uint8_t x,
		const uint8_t y,
		const uint8_t sp,
		const uint16_t pc,
		const uint8_t p
) : m_a(a),
	m_x(x),
	m_y(y),
	m_sp(sp),
	m_pc(pc),
	m_p(p) {}
