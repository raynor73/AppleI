#include "loadbinmodel.h"

LoadBinModel::LoadBinModel(Mos6502::Memory *memory, QObject *parent) :
	ModelWithState(STATE_AWAITING_DATA, parent),
	m_memory(memory) {}

void LoadBinModel::onDataReceived(QByteArray data)
{
	if (m_state == STATE_AWAITING_DATA) {
		m_data = data;
		changeState(STATE_AWAITING_START_ADDRESS);
	}
}

void LoadBinModel::onStartAddressProvided(const uint16_t address)
{
	if (m_state == STATE_AWAITING_START_ADDRESS) {
		for (int i = 0; i < m_data.size(); i++) {
			m_memory->writeByte(address + i, m_data.at(i));
		}
		changeState(STATE_AWAITING_DATA);
	}
}
