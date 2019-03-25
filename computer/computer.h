#ifndef COMPUTER_H
#define COMPUTER_H

#include "cpu6502/cpu6502.h"
#include "systembus.h"
#include "keyboard.h"
#include "display.h"
#include "rom.h"
#include "ram.h"

class Computer
{
public:
	explicit Computer(Keyboard *keyboard, Display *display);

	void clockTick();
	void reset();

	void toggleDebug();

	Ram *ram() { return &m_ram; }

private:
	Cpu6502 m_cpu;
	SystemBus m_systemBus;
	Rom m_rom;
	Ram m_ram;
};

#endif // COMPUTER_H
