#ifndef LOADBINMODEL_H
#define LOADBINMODEL_H

#include "modelwithstate.h"
#include "cpu6502/cpu6502memory.h"

class LoadBinModel : public ModelWithState
{
public:
	explicit LoadBinModel(Mos6502::Memory *memory, QObject *parent = 0);

	static const int STATE_AWAITING_DATA = 1;
	static const int STATE_AWAITING_START_ADDRESS = 2;

public slots:
	void onDataReceived(QByteArray data);
	void onStartAddressProvided(const uint16_t address);

private:
	Mos6502::Memory *m_memory;
	QByteArray m_data;
};

#endif // LOADBINMODEL_H
