#include "layer/control/penaltydefensive.h"
#include "layer/control/play.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;

PenaltyDefensive::PenaltyDefensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *PenaltyDefensive::nextState()
{
	if (m_referee.getContinuePlaying())
		return new Play(m_logger, m_referee);

	return 0;
}

string PenaltyDefensive::getName()
{
	return string("penalty defensive");
}

void PenaltyDefensive::updateInternal()
{

}