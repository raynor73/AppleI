#ifndef SYSTEMBUS_H
#define SYSTEMBUS_H

#include <forward_list>
#include "cpu6502/memory.h"
#include "device.h"

class SystemBus : public Memory
{
public:
	void addDevice(Device *device);

	virtual uint8_t readByte(const uint16_t address) override;
	virtual void writeByte(const uint16_t address, const uint8_t value) override;

private:
	std::forward_list<Device *> m_devices;
};

#endif // SYSTEMBUS_H
