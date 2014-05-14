#include "layer/control/preparekickoffoffensivetest.h"
#include "layer/control/preparekickoffoffensive.h"
#include "layer/control/kickoffoffensive.h"
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

RoboSoccerState *PrepareKickOffOffensiveTest::createInstance()
{
	return new PrepareKickOffOffensive(*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball, *m_targetPositionFetcher);
}

void PrepareKickOffOffensiveTest::update_movementFinished_refereeGotCallToSetReady()
{
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setTargetReached(true);

	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_referee->getCallsToSetReady());
}

void PrepareKickOffOffensiveTest::update_movementNotYetStarted_allRobotsGotCallToMove()
{
	m_state->update();

	RobotMock const &robot = m_ownTeam->getRobotMock();
	CPPUNIT_ASSERT_EQUAL((unsigned int)3, robot.getCallsToGoToCombined());
}

void PrepareKickOffOffensiveTest::update_movementAlreadyStarted_allRobotsGotNoAdditonalCallToMove()
{
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setTargetReached(true);

	m_state->update();
	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, robot.getCallsToGoToCombined());
}

void PrepareKickOffOffensiveTest::update_movementNotYetFinished_refereeGotNoCallToSetReady()
{
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setTargetReached(false);

	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_referee->getCallsToSetReady());
}

void PrepareKickOffOffensiveTest::nextState_movementFinishedAndExecuteKickOff_kickOffOffensive()
{
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setTargetReached(true);
	m_referee->setPrepareForKickOff(false);
	m_referee->setExecuteKickOff(true);
	m_state->update();

	State *state = m_state->nextState();

	KickOffOffensive *stateCasted = dynamic_cast<KickOffOffensive*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PrepareKickOffOffensiveTest::nextState_movementFinishedButNotExecuteKickOff_0()
{
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setTargetReached(true);
	m_referee->setPrepareForKickOff(true);
	m_referee->setExecuteKickOff(false);
	m_state->update();

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PrepareKickOffOffensiveTest::nextState_notPrepareKickOffAndNotExecuteKickOff_pause()
{
	m_referee->setPrepareForKickOff(false);
	m_referee->setExecuteKickOff(false);

	State *state = m_state->nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PrepareKickOffOffensiveTest::nextState_movementOfOneRobotNotYetFinished_0()
{
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setTargetReached(false);
	m_referee->setPrepareForKickOff(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}
