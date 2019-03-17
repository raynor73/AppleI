#ifndef ROM_H
#define ROM_H

#include "computer/device.h"

class Rom : public Device
{
public:
	Rom();

	virtual bool isUsingAddress(const uint16_t address) override;
	virtual uint8_t readByte(const uint16_t address) override;
	virtual void writeByte(const uint16_t address, const uint8_t value) override;

private:
	uint8_t m_rom[256];

	static const uint16_t LOWER_ADDRESS = 0xff00;
	//static const uint16_t HIGHER_ADDRESS = 0xffff;
};

#endif // ROM_H
