#ifndef COMPUTER_H
#define COMPUTER_H

#include "cpu6502/cpu6502.h"
#include "systembus.h"
#include "keyboard.h"
#include "display.h"
#include "rom.h"

class Computer
{
public:
	explicit Computer(Keyboard *keyboard, Display *display);

	void clockTick();
	void reset();

private:
	Cpu6502 m_cpu;
	SystemBus m_systemBus;
	Rom m_rom;
};

#endif // COMPUTER_H
