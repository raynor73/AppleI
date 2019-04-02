#ifndef SYSTEMBUS_H
#define SYSTEMBUS_H

#include <forward_list>
#include "cpu6502/cpu6502memory.h"
#include "device.h"

class SystemBus : public Mos6502::Memory
{
public:
	void addDevice(Device *device);

	virtual uint8_t readByte(const uint16_t address) override;
	virtual void writeByte(const uint16_t address, const uint8_t value) override;

private:
	std::forward_list<Device *> m_devices;
};

#endif // SYSTEMBUS_H
