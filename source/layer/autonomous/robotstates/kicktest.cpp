#include "layer/autonomous/robotstates/kicktest.h"
#include "layer/autonomous/robotstates/kick.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

RobotState *KickTest::createInstance()
{
	return new Kick(*m_controllableRobot, *m_ball, *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
}

void KickTest::targetReached_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void KickTest::nextState_noTimePassedBy_0()
{
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);

	RobotState *nextState = m_robotState->nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void KickTest::nextState_oneSecondAndRobotStillMoving_0()
{
	m_watch->setTime(4);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);

	RobotState *nextStateOne = m_robotState->nextState(false);
	m_watch->setTime(5);
	RobotState *nextStateTwo = m_robotState->nextState(false);


	CPPUNIT_ASSERT(nextStateOne == 0);
	CPPUNIT_ASSERT(nextStateTwo == 0);
}

void KickTest::nextState_robotNotMovingAnymore_reachedTarget()
{
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();

	RobotState *nextState = m_robotState->nextState(false);

	ReachedTarget *nextStateCasted = dynamic_cast<ReachedTarget*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextStateCasted;
}

void KickTest::update_severalTimesCalled_oneCallToKick()
{
	m_robotState->update();
	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToKick());
}

void KickTest::isEquivalentToDriveTo_empty_false()
{
	vector<Pose> pose;
	pose.push_back(Pose());

	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(pose));
}
