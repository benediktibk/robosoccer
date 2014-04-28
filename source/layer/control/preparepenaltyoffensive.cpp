#include "layer/control/preparepenaltyoffensive.h"
#include "layer/control/penaltyoffensive.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PreparePenaltyOffensive::PreparePenaltyOffensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false),
	m_movementFinished(false)
{ }

State *PreparePenaltyOffensive::nextState()
{
	if (m_movementFinished && m_referee.getExecutePenalty())
		return new PenaltyOffensive(m_logger, m_referee);

	return 0;
}

string PreparePenaltyOffensive::getName()
{
	return string("prepare penalty offensive");
}

void PreparePenaltyOffensive::updateInternal()
{
	//! @todo start and movement and wait for it
	m_movementFinished = true;
	m_referee.setReady();
}
