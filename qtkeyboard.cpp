#include <QKeyEvent>
#include "qtkeyboard.h"

QtKeyboard::QtKeyboard(QObject *parent) : QObject(parent) {}

bool QtKeyboard::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		switch (keyEvent->key()) {
		case Qt::Key_Return:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_CR;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Escape:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_ESC;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Space:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_SPACE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Comma:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_COMMA;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Minus:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_HYPHEN;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Period:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_PERIOD;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Slash:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_SLASH;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Colon:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_COLON;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Semicolon:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_SEMICOLON;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_0:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_0;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_1:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_1;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_2:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_2;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_3:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_3;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_4:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_4;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_5:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_5;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_6:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_6;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_7:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_7;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_8:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_8;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_9:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_9;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_A:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_A_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_B:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_B_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_C:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_C_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_D:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_D_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_E:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_E_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_F:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_F_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_G:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_G_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_H:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_H_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_I:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_I_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_J:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_J_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_K:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_K_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_L:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_L_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_M:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_M_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_N:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_N_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_O:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_O_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_P:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_P_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Q:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_Q_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_R:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_R_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_S:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_S_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_T:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_T_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_U:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_U_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_V:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_V_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_W:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_W_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_X:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_X_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Y:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_Y_UPPER_CASE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Z:
			m_keyCode = ALWAYS_SET_DATA_BITS | ASCII_CODE_Z_UPPER_CASE;
			m_hasKeyToRead = true;
			break;
		}
		return true;
	}
	else
	{
		return QObject::eventFilter(obj, event);
	}
}
