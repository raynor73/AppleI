#ifndef QTKEYBOARD_H
#define QTKEYBOARD_H

#include <QObject>
#include "computer/keyboard.h"

class QtKeyboard : public QObject, public Keyboard
{
	Q_OBJECT
public:
	explicit QtKeyboard(QObject *parent = nullptr);

	bool simulateKeystroke(const uint8_t asciiCode);

protected:
	bool eventFilter(QObject *obj, QEvent *event) override;

private:
	static const uint8_t ALWAYS_SET_DATA_BITS = 0x80;

	static const uint8_t ASCII_CODE_CR = 0x0D;
	static const uint8_t ASCII_CODE_ESC = 0x1B;

	static const uint8_t ASCII_CODE_SPACE = 0x20;
	static const uint8_t ASCII_CODE_EXCLAMATION = 0x21;
	static const uint8_t ASCII_CODE_QUOTATION = 0x22;
	static const uint8_t ASCII_CODE_NUMBER_SIGN = 0x23;
	static const uint8_t ASCII_CODE_DOLLAR = 0x24;
	static const uint8_t ASCII_CODE_PERCENT = 0x25;
	static const uint8_t ASCII_CODE_AMPERSAND = 0x26;
	static const uint8_t ASCII_CODE_APOSTROPHE = 0x27;
	static const uint8_t ASCII_CODE_LEFT_PARENTHESIS = 0x28;
	static const uint8_t ASCII_CODE_RIGHT_PARENTHESIS = 0x29;
	static const uint8_t ASCII_CODE_ASTERISK = 0x2a;
	static const uint8_t ASCII_CODE_PLUS = 0x2b;
	static const uint8_t ASCII_CODE_COMMA = 0x2C;
	static const uint8_t ASCII_CODE_HYPHEN = 0x2D;
	static const uint8_t ASCII_CODE_PERIOD = 0x2E;
	static const uint8_t ASCII_CODE_SLASH = 0x2F;

	static const uint8_t ASCII_CODE_COLON = 0x3A;
	static const uint8_t ASCII_CODE_SEMICOLON = 0x3B;
	static const uint8_t ASCII_CODE_LESS_THAN = 0x3c;
	static const uint8_t ASCII_CODE_EQUALS = 0x3d;
	static const uint8_t ASCII_CODE_GREATER_THAN = 0x3e;
	static const uint8_t ASCII_CODE_QUESTION = 0x3f;
	static const uint8_t ASCII_CODE_AT = 0x40;

	static const uint8_t ASCII_CODE_0 = 0x30;
	static const uint8_t ASCII_CODE_1 = 0x31;
	static const uint8_t ASCII_CODE_2 = 0x32;
	static const uint8_t ASCII_CODE_3 = 0x33;
	static const uint8_t ASCII_CODE_4 = 0x34;
	static const uint8_t ASCII_CODE_5 = 0x35;
	static const uint8_t ASCII_CODE_6 = 0x36;
	static const uint8_t ASCII_CODE_7 = 0x37;
	static const uint8_t ASCII_CODE_8 = 0x38;
	static const uint8_t ASCII_CODE_9 = 0x39;

	static const uint8_t ASCII_CODE_A_UPPER_CASE = 0x41;
	static const uint8_t ASCII_CODE_B_UPPER_CASE = 0x42;
	static const uint8_t ASCII_CODE_C_UPPER_CASE = 0x43;
	static const uint8_t ASCII_CODE_D_UPPER_CASE = 0x44;
	static const uint8_t ASCII_CODE_E_UPPER_CASE = 0x45;
	static const uint8_t ASCII_CODE_F_UPPER_CASE = 0x46;
	static const uint8_t ASCII_CODE_G_UPPER_CASE = 0x47;
	static const uint8_t ASCII_CODE_H_UPPER_CASE = 0x48;
	static const uint8_t ASCII_CODE_I_UPPER_CASE = 0x49;
	static const uint8_t ASCII_CODE_J_UPPER_CASE = 0x4A;
	static const uint8_t ASCII_CODE_K_UPPER_CASE = 0x4B;
	static const uint8_t ASCII_CODE_L_UPPER_CASE = 0x4C;
	static const uint8_t ASCII_CODE_M_UPPER_CASE = 0x4D;
	static const uint8_t ASCII_CODE_N_UPPER_CASE = 0x4E;
	static const uint8_t ASCII_CODE_O_UPPER_CASE = 0x4F;
	static const uint8_t ASCII_CODE_P_UPPER_CASE = 0x50;
	static const uint8_t ASCII_CODE_Q_UPPER_CASE = 0x51;
	static const uint8_t ASCII_CODE_R_UPPER_CASE = 0x52;
	static const uint8_t ASCII_CODE_S_UPPER_CASE = 0x53;
	static const uint8_t ASCII_CODE_T_UPPER_CASE = 0x54;
	static const uint8_t ASCII_CODE_U_UPPER_CASE = 0x55;
	static const uint8_t ASCII_CODE_V_UPPER_CASE = 0x56;
	static const uint8_t ASCII_CODE_W_UPPER_CASE = 0x57;
	static const uint8_t ASCII_CODE_X_UPPER_CASE = 0x58;
	static const uint8_t ASCII_CODE_Y_UPPER_CASE = 0x59;
	static const uint8_t ASCII_CODE_Z_UPPER_CASE = 0x5A;

	static const uint8_t ASCII_CODE_LEFT_SQUARE_BRACKET = 0x5B;
	static const uint8_t ASCII_CODE_BACKSLASH = 0x5C;
	static const uint8_t ASCII_CODE_RIGHT_SQUARE_BRACKET = 0x5D;
	static const uint8_t ASCII_CODE_CARET = 0x5E;
	static const uint8_t ASCII_CODE_UNDERSCORE = 0x5f;
};

#endif // QTKEYBOARD_H
