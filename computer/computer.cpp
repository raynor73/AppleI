#include "computer.h"

Computer::Computer(Keyboard *keyboard, Display *display)
{
	m_cpu.memory = &m_systemBus;
	m_systemBus.addDevice(&m_rom);
	m_systemBus.addDevice(&m_ram);
	m_systemBus.addDevice(keyboard);
	m_systemBus.addDevice(display);
}

void Computer::clockTick()
{
	m_cpu.clockTick();
}

void Computer::reset()
{
	m_cpu.reset();
}
