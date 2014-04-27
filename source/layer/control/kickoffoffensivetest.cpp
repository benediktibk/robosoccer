#include "layer/control/kickoffoffensivetest.h"
#include "layer/control/kickoffoffensive.h"
#include "layer/control/play.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *KickOffOffensiveTest::createInstance()
{
	return new KickOffOffensive(*m_logger, *m_referee);
}

void KickOffOffensiveTest::nextState_executeKickOff_0()
{
	m_referee->setExecuteKickOff(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void KickOffOffensiveTest::nextState_continuePlaying_play()
{
	m_referee->setContinuePlaying(true);

	State *state = m_state->nextState();

	Play *stateCasted = dynamic_cast<Play*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
}