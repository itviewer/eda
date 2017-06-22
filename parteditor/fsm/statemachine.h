#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "global.h"

class State;

class StateMachine : public QObject
{
    Q_OBJECT
public:
    StateMachine(QObject *parent);
    ~StateMachine();

    State* state(FSM state) const;
    FSM currentState() const;

public slots:
    void onSceneStateChanged(FSM state);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    FSM m_currentState;
    QHash<FSM,State*> states;
};

#endif // STATEMACHINE_H
