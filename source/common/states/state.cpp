#include "common/states/state.h"
#include "common/logging/logger.h"

using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

State::State(Logger &logger, bool callUpdateOnlyOnce) :
	m_logger(logger),
	m_callUpdateOnlyOnce(callUpdateOnlyOnce),
	m_updateAlreadyCalled(false)
{ }

State::~State()
{ }

void State::update()
{
	if (!(m_updateAlreadyCalled && m_callUpdateOnlyOnce))
	{
		m_logger.logToLogFileOfType(Logger::LogFileTypeStateChanges, "Updating State: " + getName());
		updateInternal();
	}

	m_updateAlreadyCalled = true;
}

bool State::allowLogMessages()
{
	return true;
}

bool State::updateAlreadyCalled() const
{
	return m_updateAlreadyCalled;
}
