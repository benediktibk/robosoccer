#include "layer/control/pausetest.h"
#include "layer/control/pause.h"
#include "layer/control/preparekickoff.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PauseTest::createInstance()
{
	return new Pause(*m_logger, *m_referee);
}

void PauseTest::nextState_prepareKickOffSet_prepareKickOff()
{
	m_referee->setPrepareForKickOff(true);

	State *state = m_state->nextState();

	PrepareKickOff *stateCasted = dynamic_cast<PrepareKickOff*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
}

void PauseTest::nextState_gamePaused_0()
{
	m_referee->setGamePaused(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}