#ifndef MODELWITHSTATE_H
#define MODELWITHSTATE_H

#include <QObject>

class ModelWithState : public QObject
{
	Q_OBJECT
public:
	explicit ModelWithState(const int initialState, QObject *parent = 0);

signals:
	void state(const int state);

protected:
	int m_state;
	void changeState(const int newState);
};

#endif // MODELWITHSTATE_H
