#include <QKeyEvent>
#include "qtkeyboard.h"

QtKeyboard::QtKeyboard(QObject *parent) : QObject(parent) {}

bool QtKeyboard::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		switch (keyEvent->key()) {
		case Qt::Key_Enter:
			m_keyCode = ASCII_CODE_CR;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Escape:
			m_keyCode = ASCII_CODE_ESC;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Space:
			m_keyCode = ASCII_CODE_SPACE;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Comma:
			m_keyCode = ASCII_CODE_COMMA;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Minus:
			m_keyCode = ASCII_CODE_HYPHEN;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Period:
			m_keyCode = ASCII_CODE_PERIOD;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Slash:
			m_keyCode = ASCII_CODE_SLASH;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Colon:
			m_keyCode = ASCII_CODE_COLON;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_Semicolon:
			m_keyCode = ASCII_CODE_SEMICOLON;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_0:
			m_keyCode = ASCII_CODE_0;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_1:
			m_keyCode = ASCII_CODE_1;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_2:
			m_keyCode = ASCII_CODE_2;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_3:
			m_keyCode = ASCII_CODE_3;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_4:
			m_keyCode = ASCII_CODE_4;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_5:
			m_keyCode = ASCII_CODE_6;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_6:
			m_keyCode = ASCII_CODE_7;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_7:
			m_keyCode = ASCII_CODE_8;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_8:
			m_keyCode = ASCII_CODE_SEMICOLON;
			m_hasKeyToRead = true;
			break;

		case Qt::Key_9:
			m_keyCode = ASCII_CODE_SEMICOLON;
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
