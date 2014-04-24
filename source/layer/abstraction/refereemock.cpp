#include "layer/abstraction/refereemock.h"

using namespace RoboSoccer::Layer::Abstraction;

FieldSide RefereeMock::getOwnFieldSide() const
{
	return FieldSideLeft;
}

bool RefereeMock::getPrepareForKickOff() const
{
	return false;
}

bool RefereeMock::getPrepareForPenalty() const
{
	return false;
}

bool RefereeMock::hasKickOffOrPenalty() const
{
	return false;
}

bool RefereeMock::getExecuteKickOff() const
{
	return false;
}

bool RefereeMock::getExecutePenalty() const
{
	return false;
}

bool RefereeMock::initFinished() const
{
	return false;
}

bool RefereeMock::isGamePaused() const
{
	return false;
}

void RefereeMock::setReady()
{ }
