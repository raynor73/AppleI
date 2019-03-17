#include "computer.h"

Computer::Computer(Keyboard *keyboard)
{
	m_cpu.memory = &m_systemBus;
	m_systemBus.addDevice(keyboard);
}

void Computer::clockTick()
{
	m_cpu.clockTick();
}
