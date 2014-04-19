#include "common/states/statemachine.h"
#include "common/states/state.h"
#include <assert.h>

using namespace std;
using namespace RoboSoccer::Common::States;

StateMachine::StateMachine(State *initialState) :
	m_currentState(initialState)
{
	assert(m_currentState != 0);
}

StateMachine::~StateMachine()
{
	delete m_currentState;
	m_currentState = 0;
}

void StateMachine::update()
{
	State *nextState = m_currentState->nextState();

	if (nextState != 0)
	{
		delete m_currentState;
		m_currentState = nextState;
	}

	m_currentState->update();
}

const State &StateMachine::getCurrentState() const
{
	return *m_currentState;
}

string StateMachine::getNameOfCurrentState() const
{
	return m_currentState->getName();
}

bool StateMachine::allowLogMessages() const
{
	return m_currentState->allowLogMessages();
}
