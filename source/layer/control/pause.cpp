#include "layer/control/pause.h"
#include "layer/control/preparekickoff.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

Pause::Pause(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, true)
{ }

State* Pause::nextState()
{
	if (m_referee.getPrepareForKickOff())
		return new PrepareKickOff(m_logger, m_referee);

	return 0;
}

string Pause::getName()
{
	return string("Pause/Init");
}

void Pause::updateInternal()
{
	//! @TODO stop all movements
}