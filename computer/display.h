#ifndef DISPLAY_H
#define DISPLAY_H

#include "computer/device.h"

class Display : public Device
{
public:
	explicit Display();

	virtual uint8_t readByte(const uint16_t address) override;
	virtual void writeByte(const uint16_t address, const uint8_t value) override;
	virtual bool isUsingAddress(const uint16_t address) override;

protected:
	bool m_isDisplayReady;

	static const uint16_t DATA_PORT = 0xd012;
	static const uint16_t CONTROL_REGISTER_PORT = 0xd013;
};

#endif // DISPLAY_H
