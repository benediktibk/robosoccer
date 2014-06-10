#include "layer/abstraction/refereemock.h"

using namespace RoboSoccer::Layer::Abstraction;

RefereeMock::RefereeMock() :
	m_prepareForKickOff(false),
	m_prepareForPenalty(false),
	m_hasKickOffOrPenalty(false),
	m_executeKickOff(false),
	m_executePenalty(false),
	m_gamePaused(false),
	m_continuePlaying(false),
	m_callsToSetReady(0),
	m_ownFieldSide(FieldSideLeft)
{ }

FieldSide RefereeMock::getOwnFieldSide() const
{
	return m_ownFieldSide;
}

bool RefereeMock::getPrepareForKickOff() const
{
	return m_prepareForKickOff;
}

bool RefereeMock::getPrepareForPenalty() const
{
	return m_prepareForPenalty;
}

bool RefereeMock::hasKickOffOrPenalty() const
{
	return m_hasKickOffOrPenalty;
}

bool RefereeMock::getExecuteKickOff() const
{
	return m_executeKickOff;
}

bool RefereeMock::getExecutePenalty() const
{
	return m_executePenalty;
}

bool RefereeMock::initFinished() const
{
	return false;
}

bool RefereeMock::isGamePaused() const
{
	return m_gamePaused;
}

bool RefereeMock::getContinuePlaying() const
{
	return m_continuePlaying;
}

void RefereeMock::setReady()
{
	++m_callsToSetReady;
}

void RefereeMock::logInformation()
{ }

void RefereeMock::setPrepareForKickOff(bool value)
{
	m_prepareForKickOff = value;
}

void RefereeMock::setPrepareForPenalty(bool value)
{
	m_prepareForPenalty = value;
}

void RefereeMock::setHasKickOffOrPenalty(bool value)
{
	m_hasKickOffOrPenalty = value;
}

void RefereeMock::setExecuteKickOff(bool value)
{
	m_executeKickOff = value;
}

void RefereeMock::setExecutePenalty(bool value)
{
	m_executePenalty = value;
}

void RefereeMock::setGamePaused(bool value)
{
	m_gamePaused = value;
}

void RefereeMock::setContinuePlaying(bool value)
{
	m_continuePlaying = value;
}

unsigned int RefereeMock::getCallsToSetReady() const
{
	return m_callsToSetReady;
}

bool RoboSoccer::Layer::Abstraction::RefereeMock::playModeChangedSinceLastCall()
{
	return false;
}

void RefereeMock::setOwnFieldSide(FieldSide fieldSide)
{
	m_ownFieldSide = fieldSide;
}
