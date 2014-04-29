#include "layer/control/playtest.h"
#include "layer/control/play.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PlayTest::createInstance()
{
	return new Play(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball);
}

void PlayTest::nextState_everythingSet_0()
{
	m_referee->setContinuePlaying(true);
	m_referee->setExecuteKickOff(true);
	m_referee->setExecutePenalty(true);
	m_referee->setPrepareForKickOff(true);
	m_referee->setPrepareForPenalty(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PlayTest::nextState_notContinuePlaying_pause()
{
	m_referee->setContinuePlaying(false);
	m_referee->setExecuteKickOff(true);
	m_referee->setExecutePenalty(true);
	m_referee->setPrepareForKickOff(true);
	m_referee->setPrepareForPenalty(true);

	State *state = m_state->nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}
