#include "layer/control/penaltydefensivetest.h"
#include "layer/control/penaltydefensive.h"
#include "layer/control/play.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PenaltyDefensiveTest::createInstance()
{
	return new PenaltyDefensive(*m_logger, *m_referee);
}

void PenaltyDefensiveTest::nextState_executePenalty_0()
{
	m_referee->setExecutePenalty(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PenaltyDefensiveTest::nextState_continuePlaying_play()
{
	m_referee->setContinuePlaying(true);

	State *state = m_state->nextState();

	Play *stateCasted = dynamic_cast<Play*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
}