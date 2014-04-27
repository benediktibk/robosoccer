#include "layer/control/kickoffdefensivetest.h"
#include "layer/control/kickoffdefensive.h"
#include "layer/control/play.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *KickOffDefensiveTest::createInstance()
{
	return new KickOffDefensive(*m_logger, *m_referee);
}

void KickOffDefensiveTest::nextState_executeKickOff_0()
{
	m_referee->setExecuteKickOff(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void KickOffDefensiveTest::nextState_continuePlaying_play()
{
	m_referee->setContinuePlaying(true);

	State *state = m_state->nextState();

	Play *stateCasted = dynamic_cast<Play*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
}