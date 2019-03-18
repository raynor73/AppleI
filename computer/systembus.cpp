#include <QDebug>
#include "systembus.h"

void SystemBus::addDevice(Device *device)
{
	m_devices.push_front(device);
}

uint8_t SystemBus::readByte(const uint16_t address)
{
	for (std::forward_list<Device *>::iterator it = m_devices.begin(); it != m_devices.end(); ++it)
	{
		if ((*it)->isUsingAddress(address))
		{
			return (*it)->readByte(address);
		}
	}

	qDebug("No device found to read from address: 0x%04x", address);

	return 0;
}

void SystemBus::writeByte(const uint16_t address, const uint8_t value)
{
	for (std::forward_list<Device *>::iterator it = m_devices.begin(); it != m_devices.end(); ++it)
	{
		if ((*it)->isUsingAddress(address))
		{
			(*it)->writeByte(address, value);
			return;
		}
	}

	qDebug("No device found to write to address: 0x%04x value: 0x%02x", address, value);
}
