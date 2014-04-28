#include "layer/control/preparekickoffdefensivetest.h"
#include "layer/control/preparekickoffdefensive.h"
#include "layer/control/kickoffdefensive.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PrepareKickOffDefensiveTest::createInstance()
{
	return new PrepareKickOffDefensive(*m_logger, *m_referee);
}

void PrepareKickOffDefensiveTest::update_movementFinished_refereeGotCallToSetReady()
{
	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_referee->getCallsToSetReady());
}

void PrepareKickOffDefensiveTest::nextState_movementFinished_kickOffDefensive()
{
	m_referee->setPrepareForKickOff(true);
	m_state->update();

	State *state = m_state->nextState();

	KickOffDefensive *stateCasted = dynamic_cast<KickOffDefensive*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PrepareKickOffDefensiveTest::nextState_prepareKickOff_0()
{
	m_referee->setPrepareForKickOff(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}