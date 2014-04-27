#include "layer/control/kickoffdefensive.h"
#include "layer/control/play.h"
#include "layer/abstraction/refereemock.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;

KickOffDefensive::KickOffDefensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *KickOffDefensive::nextState()
{
	if (m_referee.getContinuePlaying())
		return new Play(m_logger, m_referee);

	return 0;
}

string KickOffDefensive::getName()
{
	return string("kick off defensive");
}

void KickOffDefensive::updateInternal()
{

}