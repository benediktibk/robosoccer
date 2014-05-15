#include "layer/autonomous/robotstatekicktest.h"
#include "layer/autonomous/robotstatekick.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotState *RobotStateKickTest::createInstance()
{
	return new RobotStateKick(*m_controllableRobot, 30, *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
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
	m_robotState->update();

	RobotState *nextState = m_robotState->nextState();

	CPPUNIT_ASSERT(nextState == 0);
}

void RobotStateKickTest::nextState_oneSecondWaited_followingState()
{
	m_watch->setTime(4);
	m_robotState->update();

	RobotState *nextStateOne = m_robotState->nextState();
	m_watch->setTime(5);
	RobotState *nextStateTwo = m_robotState->nextState();

	CPPUNIT_ASSERT(nextStateOne == 0);
	RobotStateReachedTarget *nextStateCasted = dynamic_cast<RobotStateReachedTarget*>(nextStateTwo);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextStateTwo;
}

void RobotStateKickTest::update_severalTimesCalled_oneCallToKick()
{
	m_robotState->update();
	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToKick());
}

void RobotStateKickTest::isEquivalentToDriveTo_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Pose()));
}
