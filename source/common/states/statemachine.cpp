#include "common/states/statemachine.h"
#include "common/states/state.h"
#include "common/logging/logger.h"
#include <sstream>
#include <assert.h>

using namespace std;
using namespace RoboSoccer::Common::States;

StateMachine::StateMachine(State *initialState) :
	m_currentState(initialState),
	m_logger(initialState->getLogger())
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
		logStateChange(nextState->getName());
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

void StateMachine::logStateChange(const string &stateName)
{
	stringstream stream;
	stream << "switching into state " << stateName;
	m_logger.logToLogFileOfType(Logging::Logger::LogFileTypeStateChanges, stream.str());
}
