#include "common/states/statemock.h"

using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace std;

StateMock::StateMock(Logger &logger) :
	State(logger, false),
	m_callsToNextState(0),
	m_callsToUpdate(0),
	m_nextState(0)
{ }

StateMock::StateMock(Logger &logger, bool callUpdateOnlyOnce) :
	State(logger, callUpdateOnlyOnce),
	m_callsToNextState(0),
	m_callsToUpdate(0),
	m_nextState(0)
{ }

State *StateMock::nextState()
{
	++m_callsToNextState;
	return m_nextState;
}

string StateMock::getName()
{
	return "StateMock";
}

void StateMock::updateInternal()
{
	++m_callsToUpdate;
}

unsigned int StateMock::getCallsToNextState() const
{
	return m_callsToNextState;
}

unsigned int StateMock::getCallsToUpdate() const
{
	return m_callsToUpdate;
}

void StateMock::setNextState(State *state)
{
	m_nextState = state;
}
