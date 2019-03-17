#ifndef COMPUTER_H
#define COMPUTER_H

#include "cpu6502/cpu6502.h"
#include "systembus.h"
#include "keyboard.h"

class Computer
{
public:
	explicit Computer(Keyboard *keyboard);

	void clockTick();

private:
	Cpu6502 m_cpu;
	SystemBus m_systemBus;
};

#endif // COMPUTER_H
