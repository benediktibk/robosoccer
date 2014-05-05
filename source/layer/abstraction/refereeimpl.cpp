#include "layer/abstraction/refereeimpl.h"
#include "common/logging/logger.h"
#include <referee.h>
#include <assert.h>
#include <sstream>

using namespace std;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;

RefereeImpl::RefereeImpl(KogniMobil::RTDBConn &dataBase, TeamColor ownColor, Logger &logger) :
	m_logger(logger),
	m_referee(new Referee(dataBase)),
	m_ownColor(ownColor),
	m_lastPlayMode(REFEREE_INIT)
{
	m_referee->Init();
}

RefereeImpl::~RefereeImpl()
{
	delete m_referee;
	m_referee = 0;
}

FieldSide RefereeImpl::getOwnFieldSide() const
{
	eSide blueSide = m_referee->GetBlueSide();

	if (blueSide == LEFT_SIDE)
	{
		switch(m_ownColor)
		{
		case TeamColorBlue:
			return FieldSideLeft;
		case TeamColorRed:
			return FieldSideRight;
		}
	}
	else if (blueSide == RIGHT_SIDE)
	{
		switch(m_ownColor)
		{
		case TeamColorBlue:
			return FieldSideRight;
		case TeamColorRed:
			return FieldSideLeft;
		}
	}

	return FieldSideInvalid;
}

bool RefereeImpl::getPrepareForKickOff() const
{
	return m_referee->GetPlayMode() == BEFORE_KICK_OFF;
}

bool RefereeImpl::getPrepareForPenalty() const
{
	return m_referee->GetPlayMode() == BEFORE_PENALTY;
}

bool RefereeImpl::hasKickOffOrPenalty() const
{
	eSide sideWithKickOffOrPenalty = m_referee->GetSide();

	switch(getOwnFieldSide())
	{
	case FieldSideLeft:
		return sideWithKickOffOrPenalty == LEFT_SIDE;
	case FieldSideRight:
		return sideWithKickOffOrPenalty == RIGHT_SIDE;
	case FieldSideInvalid:
		break;
	}

	return false;
}

bool RefereeImpl::getExecuteKickOff() const
{
	return m_referee->GetPlayMode() == KICK_OFF;
}

bool RefereeImpl::getExecutePenalty() const
{
	return m_referee->GetPlayMode() == PENALTY;
}

bool RefereeImpl::initFinished() const
{
	return m_referee->GetPlayMode() != REFEREE_INIT;
}

bool RefereeImpl::isGamePaused() const
{
	ePlayMode playMode = m_referee->GetPlayMode();
	return playMode == PAUSE || playMode == TIME_OVER;
}

bool RefereeImpl::getContinuePlaying() const
{
	ePlayMode playMode = m_referee->GetPlayMode();
	return playMode == PLAY_ON;
}

void RefereeImpl::logInformation()
{
	logBool("prepare for kick off", getPrepareForKickOff());
	logBool("prepare for penalty", getPrepareForPenalty());
	logBool("has kick off or penalty", hasKickOffOrPenalty());
	logBool("execute kick off", getExecuteKickOff());
	logBool("execute penalty", getExecutePenalty());
	logBool("init finished", initFinished());
	logBool("game paused", isGamePaused());
	logBool("continue playing", getContinuePlaying());
	logFieldSide("own field side", getOwnFieldSide());
}

void RefereeImpl::logBool(const char *message, bool value)
{
	logBool(string(message), value);
}

void RefereeImpl::logBool(string const &message, bool value)
{
	stringstream stream;
	string valueAsString = value ? "yes" : "no";
	stream << message << ": " << valueAsString;
	m_logger.logToLogFileOfType(Logger::LogFileTypeReferee, stream.str());
}

void RefereeImpl::logFieldSide(const char *message, FieldSide fieldSide)
{
	stringstream stream;
	stream << string(message) << ": " << fieldSide;
	m_logger.logToLogFileOfType(Logger::LogFileTypeReferee, stream.str());
}

void RefereeImpl::setReady()
{
	switch(m_ownColor)
	{
	case TeamColorBlue:
		m_referee->SetBlueReady();
		break;
	case TeamColorRed:
		m_referee->SetRedReady();
		break;
	}
}

bool RefereeImpl::playModeChangedSinceLastCall()
{
	ePlayMode currentMode = m_referee->GetPlayMode();
	bool result = currentMode != m_lastPlayMode;
	m_lastPlayMode = currentMode;
	return result;
}
