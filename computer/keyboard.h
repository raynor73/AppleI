#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "computer/device.h"

class Keyboard : public Device
{
public:
	explicit Keyboard();

	virtual uint8_t readByte(const uint16_t address) override;
	virtual void writeByte(const uint16_t address, const uint8_t value) override;
	virtual bool isUsingAddress(const uint16_t address) override;

protected:
	bool m_hasKeyToRead;
	uint8_t m_keyCode;

private:
	static const uint16_t DATA_PORT = 0xd010;
	static const uint16_t CONTROL_REGISTER_PORT = 0xd011;
};

#endif // KEYBOARD_H
