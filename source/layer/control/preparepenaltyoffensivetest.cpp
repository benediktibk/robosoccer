#include "layer/control/preparepenaltyoffensivetest.h"
#include "layer/control/preparepenaltyoffensive.h"
#include "layer/control/penaltyoffensive.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PreparePenaltyOffensiveTest::createInstance()
{
	return new PreparePenaltyOffensive(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
}

void PreparePenaltyOffensiveTest::update_movementFinished_refereeGotCallToSetReady()
{
	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_referee->getCallsToSetReady());
}

void PreparePenaltyOffensiveTest::nextState_movementFinishedAndExecutePenalty_penaltyOffensive()
{
	m_referee->setPrepareForPenalty(false);
	m_referee->setExecutePenalty(true);
	m_state->update();

	State *state = m_state->nextState();

	PenaltyOffensive *stateCasted = dynamic_cast<PenaltyOffensive*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PreparePenaltyOffensiveTest::nextState_movementFinishedButNotExecutePenalty_0()
{
	m_referee->setPrepareForPenalty(true);
	m_referee->setExecutePenalty(false);
	m_state->update();

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PreparePenaltyOffensiveTest::nextState_preparePenalty_0()
{
	m_referee->setPrepareForPenalty(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PreparePenaltyOffensiveTest::nextState_notPreparePenaltyAndNotExecutePenalty_pause()
{
	m_referee->setPrepareForPenalty(false);
	m_referee->setExecutePenalty(false);

	State *state = m_state->nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}