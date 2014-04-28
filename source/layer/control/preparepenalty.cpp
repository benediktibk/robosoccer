#include "layer/control/preparepenalty.h"
#include "layer/control/preparepenaltyoffensive.h"
#include "layer/control/preparepenaltydefensive.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PreparePenalty::PreparePenalty(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false)
{ }

State *PreparePenalty::nextState()
{
	if (m_referee.hasKickOffOrPenalty())
		return new PreparePenaltyOffensive(m_logger, m_referee);
	else
		return new PreparePenaltyDefensive(m_logger, m_referee);
}

string PreparePenalty::getName()
{
	return string("prepare penalty");
}

void PreparePenalty::updateInternal()
{ }