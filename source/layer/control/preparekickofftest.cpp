#include "layer/control/preparekickofftest.h"
#include "layer/control/preparekickoff.h"
#include "layer/control/preparekickoffoffensive.h"
#include "layer/control/preparekickoffdefensive.h"
#include "layer/abstraction/refereemock.h"
#include "layer/autonomous/enemyteamimpl.h"
#include "layer/autonomous/teamimpl.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PrepareKickOffTest::createInstance()
{
	return new PrepareKickOff(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
}

void PrepareKickOffTest::nextState_executeKickOff_prepareState()
{
	m_referee->setExecuteKickOff(true);

	State *state = m_state->nextState();

	PrepareKickOffOffensive *stateOffensive = dynamic_cast<PrepareKickOffOffensive*>(state);
	PrepareKickOffDefensive *stateDefensive = dynamic_cast<PrepareKickOffDefensive*>(state);
	CPPUNIT_ASSERT(stateOffensive != 0 || stateDefensive != 0);
	delete state;
}

void PrepareKickOffTest::nextState_hasKickOff_prepareKickOffOffensive()
{
	m_referee->setPrepareForKickOff(true);
	m_referee->setHasKickOffOrPenalty(true);

	State *state = m_state->nextState();

	PrepareKickOffOffensive *stateCasted = dynamic_cast<PrepareKickOffOffensive*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PrepareKickOffTest::nextState_hasNotKickOff_prepareKickOffDefensive()
{
	m_referee->setPrepareForKickOff(true);
	m_referee->setHasKickOffOrPenalty(false);

	State *state = m_state->nextState();

	PrepareKickOffDefensive *stateCasted = dynamic_cast<PrepareKickOffDefensive*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}
