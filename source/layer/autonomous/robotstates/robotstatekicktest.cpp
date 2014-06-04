#include "layer/autonomous/robotstates/robotstatekicktest.h"
#include "layer/autonomous/robotstates/robotstatekick.h"
#include "layer/autonomous/robotstates/robotstatereachedtarget.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotState *RobotStateKickTest::createInstance()
{
	return new RobotStateKick(*m_controllableRobot, *m_ball, *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
}

void RobotStateKickTest::targetReached_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void RobotStateKickTest::cantReachTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->cantReachTarget());
}

void RobotStateKickTest::nextState_noTimePassedBy_0()
{
	m_robotState->update(false);
	m_controllableRobot->setIsMoving(true);

	RobotState *nextState = m_robotState->nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void RobotStateKickTest::nextState_oneSecondAndRobotStillMoving_0()
{
	m_watch->setTime(4);
	m_robotState->update(false);
	m_controllableRobot->setIsMoving(true);

	RobotState *nextStateOne = m_robotState->nextState(false);
	m_watch->setTime(5);
	RobotState *nextStateTwo = m_robotState->nextState(false);


	CPPUNIT_ASSERT(nextStateOne == 0);
	CPPUNIT_ASSERT(nextStateTwo == 0);
}

void RobotStateKickTest::nextState_robotNotMovingAnymore_reachedTarget()
{
	m_controllableRobot->setIsMoving(false);

	RobotState *nextState = m_robotState->nextState(false);

	RobotStateReachedTarget *nextStateCasted = dynamic_cast<RobotStateReachedTarget*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextStateCasted;
}

void RobotStateKickTest::update_severalTimesCalled_oneCallToKick()
{
	m_robotState->update(false);
	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToKick());
}

void RobotStateKickTest::isEquivalentToDriveTo_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Pose()));
}
