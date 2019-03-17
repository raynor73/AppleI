#ifndef QTDISPLAY_H
#define QTDISPLAY_H

#include <QObject>
#include "computer/display.h"
#include "console.h"

class QtDisplay : public QObject, public Display
{
	Q_OBJECT
public:
	explicit QtDisplay(Console *consoleWidget, QObject *parent = 0);

	virtual void writeByte(const uint16_t address, const uint8_t value) override;

private:
	Console *m_consoleWidget;
	char m_charArray[2];
};

#endif // QTDISPLAY_H
