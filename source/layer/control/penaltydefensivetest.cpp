#include "layer/control/penaltydefensivetest.h"
#include "layer/control/penaltydefensive.h"
#include "layer/control/play.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereemock.h"
#include "layer/abstraction/fieldpositioncheckergoalkeeper.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/robotmock.h"
#include "common/logging/loggermock.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Common::Geometry;

RoboSoccerState *PenaltyDefensiveTest::createInstance()
{
	return new PenaltyDefensive(
				*m_logger, *m_referee, *m_ownTeam, *m_enemyTeam, *m_ball,
				*m_targetPositionFetcher, *m_fieldPositionCheckerGoalKeeper);
}

void PenaltyDefensiveTest::nextState_executePenalty_0()
{
	m_referee->setExecutePenalty(true);

	State *state = m_state->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void PenaltyDefensiveTest::nextState_continuePlaying_play()
{
	m_referee->setContinuePlaying(true);

	State *state = m_state->nextState();

	Play *stateCasted = dynamic_cast<Play*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PenaltyDefensiveTest::nextState_notExecutePenaltyAndNotContinuePlaying_pause()
{
	m_referee->setContinuePlaying(false);
	m_referee->setExecutePenalty(false);

	State *state = m_state->nextState();

	Pause *stateCasted = dynamic_cast<Pause*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void PenaltyDefensiveTest::update_robotInsideGoalzone_oneRobotGotCallToGoToDirect()
{
	m_referee->setContinuePlaying(true);
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setCurrentPose(Pose(Point(-1.3,0.2), Angle()));

	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, robot.getCallsToGoToDirect());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, robot.getCallsToGoTo());
}

void PenaltyDefensiveTest::update_robotInsideGoalzoneAndUpdateTwiceCalled_twoCallsToGoToDirect()
{
	m_referee->setContinuePlaying(true);
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setCurrentPose(Pose(Point(-1.3,0), Angle()));

	m_state->update();
	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, robot.getCallsToGoToDirect());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, robot.getCallsToGoTo());
}

void PenaltyDefensiveTest::update_robotNotInsideGoalZone_callToGoTo()
{
	m_referee->setContinuePlaying(true);
	RobotMock &robot = m_ownTeam->getRobotMock();
	robot.setCurrentPose(Pose(Point(0.7,0.2), Angle()));

	m_state->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, robot.getCallsToGoTo());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, robot.getCallsToGoToDirect());
}
