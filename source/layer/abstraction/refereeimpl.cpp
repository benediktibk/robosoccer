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
	m_lastPlayMode(REFEREE_INIT),
	m_currentPlayMode(REFEREE_INIT)
{
	m_referee->Init();
}

RefereeImpl::~RefereeImpl()
{
	delete m_referee;
	m_referee = 0;
}

void RefereeImpl::update()
{
	m_lastPlayMode = m_currentPlayMode;
	m_currentPlayMode = m_referee->GetPlayMode();
	m_currentBlueSide = m_referee->GetBlueSide();

	if (playModeChangedSinceLastCall())
		logPlayMode(m_currentPlayMode);
}

FieldSide RefereeImpl::getOwnFieldSide() const
{
	if (m_currentBlueSide == LEFT_SIDE)
	{
		switch(m_ownColor)
		{
		case TeamColorBlue:
			return FieldSideLeft;
		case TeamColorRed:
			return FieldSideRight;
		}
	}
	else if (m_currentBlueSide == RIGHT_SIDE)
	{
		switch(m_ownColor)
		{
		case TeamColorBlue:
			return FieldSideRight;
		case TeamColorRed:
			return FieldSideLeft;
		}
	}

	m_logger.logErrorToConsoleAndWriteToGlobalLogFile("GetBlueSide returns: OWN_SIDE");
	return FieldSideInvalid;
}

bool RefereeImpl::getPrepareForKickOff() const
{
	return m_currentPlayMode == BEFORE_KICK_OFF;
}

bool RefereeImpl::getPrepareForPenalty() const
{
	return m_currentPlayMode == BEFORE_PENALTY;
}

bool RefereeImpl::hasKickOffOrPenalty() const
{
	switch(getOwnFieldSide())
	{
	case FieldSideLeft:
		return m_currentBlueSide == LEFT_SIDE;
	case FieldSideRight:
		return m_currentBlueSide == RIGHT_SIDE;
	case FieldSideInvalid:
		break;
	}

	return false;
}

bool RefereeImpl::getExecuteKickOff() const
{
	return m_currentPlayMode == KICK_OFF;
}

bool RefereeImpl::getExecutePenalty() const
{
	return m_currentPlayMode == PENALTY;
}

bool RefereeImpl::initFinished() const
{
	return m_currentPlayMode != REFEREE_INIT;
}

bool RefereeImpl::isGamePaused() const
{
	ePlayMode playMode = m_currentPlayMode;
	return playMode == PAUSE || playMode == TIME_OVER;
}

bool RefereeImpl::getContinuePlaying() const
{
	ePlayMode playMode = m_currentPlayMode;
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
	logPlayMode(m_currentPlayMode);
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
	m_logger.logToLogFileOfType(Logger::LogFileTypeReferee, "sending ready signal");

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
	return m_lastPlayMode != m_currentPlayMode;
}

void RefereeImpl::logPlayMode(ePlayMode playMode)
{
	stringstream stream;
	stream << "play mode: ";
	switch(playMode)
	{
	case REFEREE_INIT:
		stream << "REFEREE_INIT";
		break;
	case BEFORE_KICK_OFF:
		stream << "BEFORE_KICK_OFF";
		break;
	case KICK_OFF:
		stream << "KICK_OFF";
		break;
	case BEFORE_PENALTY:
		stream << "BEFORE_PENALTY";
		break;
	case PENALTY:
		stream << "PENALTY";
		break;
	case PAUSE:
		stream << "PAUSE";
		break;
	case TIME_OVER:
		stream << "TIME_OVER";
		break;
	case PLAY_ON:
		stream << "PLAY_ON";
		break;
	}

	m_logger.logToLogFileOfType(Logger::LogFileTypeReferee, stream.str());
}
