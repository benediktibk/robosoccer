#include "layer/control/preparekickoffoffensivetest.h"
#include "layer/control/preparekickoffoffensive.h"
#include "layer/control/kickoffoffensive.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PrepareKickOffOffensiveTest::createInstance()
{
	return new PrepareKickOffOffensive(*m_logger, *m_referee);
}

void PrepareKickOffOffensiveTest::update_movementFinished_refereeGotCallToSetReady()
{
	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_referee->getCallsToSetReady());
}

void PrepareKickOffOffensiveTest::nextState_movementFinished_kickOffOffensive()
{
	m_referee->setPrepareForKickOff(true);
	m_state->update();

	State *state = m_state->nextState();

	KickOffOffensive *stateCasted = dynamic_cast<KickOffOffensive*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PrepareKickOffOffensiveTest::nextState_prepareKickOff_0()
{
	m_referee->setPrepareForKickOff(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}