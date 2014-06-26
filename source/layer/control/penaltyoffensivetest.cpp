#include "layer/control/penaltyoffensivetest.h"
#include "layer/control/penaltyoffensive.h"
#include "layer/control/play.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereemock.h"
#include "layer/abstraction/fieldpositioncheckergoalkeeper.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/robotmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::States;

RoboSoccerState *PenaltyOffensiveTest::createInstance()
{
	return new PenaltyOffensive(
				*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball,
				*m_targetPositionFetcher, *m_fieldPositionCheckerGoalKeeper);
}

void PenaltyOffensiveTest::nextState_executePenalty_0()
{
	m_referee->setExecutePenalty(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PenaltyOffensiveTest::nextState_continuePlaying_play()
{
	m_referee->setContinuePlaying(true);

	State *state = m_state->nextState();

	Play *stateCasted = dynamic_cast<Play*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PenaltyOffensiveTest::nextState_notExecutePenaltyAndNotContinuePlaying_pause()
{
	m_referee->setContinuePlaying(false);
	m_referee->setExecutePenalty(false);

	State *state = m_state->nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PenaltyOffensiveTest::update_onceCalled_noCallToKick()
{
	m_referee->setExecutePenalty(true);

	m_state->update();

	RobotMock const &robot = m_ownTeam->getRobotMock();
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, robot.getCallsToKick());
}

void PenaltyOffensiveTest::update_twiceCalled_noCallToKick()
{
	m_referee->setExecutePenalty(true);

	m_state->update();
	m_state->update();

	RobotMock const &robot = m_ownTeam->getRobotMock();
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, robot.getCallsToKick());
}

void PenaltyOffensiveTest::update_onceCalled_oneCallToMove()
{
	m_referee->setExecutePenalty(true);

	m_state->update();

	RobotMock const &robot = m_ownTeam->getRobotMock();
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, robot.getCallsToGoTo());
}

void PenaltyOffensiveTest::update_twiceCalled_oneCallToMove()
{
	m_referee->setExecutePenalty(true);

	m_state->update();
	m_state->update();

	RobotMock const &robot = m_ownTeam->getRobotMock();
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, robot.getCallsToGoTo());
}

void PenaltyOffensiveTest::update_twiceCalled_firstMoveThenKick()
{
	m_referee->setExecutePenalty(true);
	RobotMock &robot = m_ownTeam->getRobotMock();

	m_state->update();
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, robot.getCallsToGoTo());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, robot.getCallsToKick());

	robot.setTargetReached(true);
	m_state->update();
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, robot.getCallsToKick());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, robot.getCallsToGoTo());
}

void PenaltyOffensiveTest::update_onceCalled_callToMoveIsSlowlyAtTheEndAndIgnoringBall()
{
	m_referee->setExecutePenalty(true);
	RobotMock &robot = m_ownTeam->getRobotMock();

	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, robot.getCallsToGoTo());
	CPPUNIT_ASSERT_EQUAL(DriveModeIgnoreBallAndDriveSlowlyAtTheEnd, robot.getLastGoToDriveMode());
}
