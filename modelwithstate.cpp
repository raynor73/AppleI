#include <QException>
#include "modelwithstate.h"

ModelWithState::ModelWithState(const int initialState, QObject *parent) :
	QObject(parent),
	m_state(initialState) {}

void ModelWithState::changeState(const int newState)
{
	if (m_state == newState)
	{
		throw QException();
	}

	m_state = newState;
	emit state(m_state);
}
