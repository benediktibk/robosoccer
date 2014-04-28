#include "layer/control/preparepenaltydefensive.h"
#include "layer/control/penaltydefensive.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PreparePenaltyDefensive::PreparePenaltyDefensive(Logger &logger, RefereeBase &referee) :
	RoboSoccerState(logger, referee, false),
	m_movementFinished(false)
{ }

State *PreparePenaltyDefensive::nextState()
{
	if (m_movementFinished)
		return new PenaltyDefensive(m_logger, m_referee);

	return 0;
}

string PreparePenaltyDefensive::getName()
{
	return string("prepare penalty defensive");
}

void PreparePenaltyDefensive::updateInternal()
{
	//! @todo start and movement and wait for it
	m_movementFinished = true;
	m_referee.setReady();
}