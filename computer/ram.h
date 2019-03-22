#ifndef RAM_H
#define RAM_H

#include "computer/device.h"

class Ram : public Device
{
public:
	explicit Ram();

	virtual bool isUsingAddress(const uint16_t address) override;
	virtual uint8_t readByte(const uint16_t address) override;
	virtual void writeByte(const uint16_t address, const uint8_t value) override;

private:
	uint8_t m_ram[0x8000];

	static const uint16_t HIGHER_ADDRESS = 0x8000;
};

#endif // RAM_H
