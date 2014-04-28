#include "layer/control/preparekickoffoffensive.h"
#include "layer/control/kickoffoffensive.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PrepareKickOffOffensive::PrepareKickOffOffensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false),
	m_movementFinished(false)
{ }

State *PrepareKickOffOffensive::nextState()
{
	if (m_movementFinished && m_referee.getExecuteKickOff())
		return new KickOffOffensive(m_logger, m_referee);

	return 0;
}

string PrepareKickOffOffensive::getName()
{
	return string("prepare kick off offensive");
}

void PrepareKickOffOffensive::updateInternal()
{
	//! @todo start and movement and wait for it
	m_movementFinished = true;
	m_referee.setReady();
}
