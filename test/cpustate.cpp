#include "cpustate.h"


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
