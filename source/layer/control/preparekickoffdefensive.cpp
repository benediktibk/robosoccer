#include "layer/control/preparekickoffdefensive.h"
#include "layer/control/kickoffdefensive.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PrepareKickOffDefensive::PrepareKickOffDefensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false),
	m_movementFinished(false)
{ }

State *PrepareKickOffDefensive::nextState()
{
	if (m_movementFinished)
		return new KickOffDefensive(m_logger, m_referee);

	return 0;
}

string PrepareKickOffDefensive::getName()
{
	return string("prepare kick off defensive");
}

void PrepareKickOffDefensive::updateInternal()
{
	//! @todo start and movement and wait for it
	m_movementFinished = true;
	m_referee.setReady();
}