#include "layer/control/userinputfetchermock.h"

using namespace RoboSoccer::Layer::Control;

UserInputFetcherMock::UserInputFetcherMock() :
	m_selectionMade(false),
	m_playOffensive(false),
	m_callsToUpdate(0)
{ }

bool UserInputFetcherMock::selectionMade() const
{
	return m_selectionMade;
}

bool UserInputFetcherMock::playOffensive() const
{
	return m_playOffensive;
}

void UserInputFetcherMock::update()
{
	++m_callsToUpdate;
}

void UserInputFetcherMock::setSelectionMade(bool value)
{
	m_selectionMade = value;
}

void UserInputFetcherMock::setPlayOffensive(bool value)
{
	m_playOffensive = value;
}

unsigned int UserInputFetcherMock::getCallsToUpdate() const
{
	return m_callsToUpdate;
}
