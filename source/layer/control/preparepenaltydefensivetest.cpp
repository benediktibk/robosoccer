#include "layer/control/preparepenaltydefensivetest.h"
#include "layer/control/preparepenaltydefensive.h"
#include "layer/control/penaltydefensive.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereemock.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/robotmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PreparePenaltyDefensiveTest::createInstance()
{
	return new PreparePenaltyDefensive(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
}

void PreparePenaltyDefensiveTest::update_movementFinished_refereeGotCallToSetReady()
{
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setTargetReached(true);
	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_referee->getCallsToSetReady());
}

void PreparePenaltyDefensiveTest::update_movementNotYetStarted_allRobotsGotCallToMove()
{
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setTargetReached(true);

	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_referee->getCallsToSetReady());
}

void PreparePenaltyDefensiveTest::update_movementAlreadyStarted_allRobotsGotNoAdditionalCallToMove()
{
	m_state->update();

	RobotMock const &robot = m_ownTeam->getRobotMock();
	CPPUNIT_ASSERT_EQUAL((unsigned int)3, robot.getCallsToGoTo());
}

void PreparePenaltyDefensiveTest::update_movementNotYetFinished_refereeGotNoCallToSetReady()
{
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setTargetReached(true);

	m_state->update();
	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, robot.getCallsToGoTo());
}

void PreparePenaltyDefensiveTest::nextState_movementFinishedAndExecutePenalty_penaltyDefensive()
{
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setTargetReached(true);
	m_referee->setPrepareForPenalty(false);
	m_referee->setExecutePenalty(true);
	m_state->update();

	State *state = m_state->nextState();

	PenaltyDefensive *stateCasted = dynamic_cast<PenaltyDefensive*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PreparePenaltyDefensiveTest::nextState_movementFinishedButNotExecutePenalty_0()
{
	m_referee->setPrepareForPenalty(true);
	m_referee->setExecutePenalty(false);
	m_state->update();

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PreparePenaltyDefensiveTest::nextState_preparePenalty_0()
{
	m_referee->setPrepareForPenalty(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PreparePenaltyDefensiveTest::nextState_notPreparePenaltyAndNotExecutePenalty_pause()
{
	m_referee->setPrepareForPenalty(false);
	m_referee->setExecutePenalty(false);

	State *state = m_state->nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PreparePenaltyDefensiveTest::nextState_movementOfOneRobotNotYetFinished_0()
{
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setTargetReached(false);
	m_referee->setPrepareForPenalty(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}