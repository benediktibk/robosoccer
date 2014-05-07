#include "layer/autonomous/robotstatedrivetotest.h"
#include "layer/autonomous/robotstatedriveto.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotState *RobotStateDriveToTest::createInstance()
{
	return new RobotStateDriveTo(*m_controllableRobot, Point(3, 2), *m_watch);
}

void RobotStateDriveToTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void RobotStateDriveToTest::cantReachTarget_noObstacles_false()
{
	CPPUNIT_ASSERT(!m_robotState->cantReachTarget());
}

void RobotStateDriveToTest::nextState_targetNotYetReached_0()
{
	m_controllableRobot->setPose(Pose(Point(-1, -3), Angle()));

	RobotState *nextState = m_robotState->nextState();

	CPPUNIT_ASSERT(0 == nextState);
}

void RobotStateDriveToTest::nextState_targetReached_targetReachedState()
{
	m_controllableRobot->setPose(Pose(Point(3, 2), Angle()));

	RobotState *nextState = m_robotState->nextState();

	RobotStateReachedTarget *nextStateCasted = dynamic_cast<RobotStateReachedTarget*>(nextState);
	CPPUNIT_ASSERT(0 != nextStateCasted);
	delete nextState;
}

void RobotStateDriveToTest::nextState_took10s_targetReachedState()
{
	m_watch->setTime(10);

	RobotState *nextState = m_robotState->nextState();

	RobotStateReachedTarget *nextStateCasted = dynamic_cast<RobotStateReachedTarget*>(nextState);
	CPPUNIT_ASSERT(0 != nextStateCasted);
	delete nextState;
}

void RobotStateDriveToTest::nextState_took10sWithSeveralCalls_targetReachedState()
{
	RobotState *nextState = 0;

	for (unsigned int i = 0; i < 100; ++i)
	{
		m_watch->setTime(i*10.0/100);
		nextState = m_robotState->nextState();

		if (nextState != 0)
			break;
	}

	RobotStateReachedTarget *nextStateCasted = dynamic_cast<RobotStateReachedTarget*>(nextState);
	CPPUNIT_ASSERT(0 != nextStateCasted);
	delete nextState;
}

void RobotStateDriveToTest::update_noObstacles_callToGoToPrecise()
{
	m_controllableRobot->setPose(Pose(Point(-1, -3), Angle()));

	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void RobotStateDriveToTest::update_noChangesInTarget_onlyOneCallToGoToPrecise()
{
	m_controllableRobot->setPose(Pose(Point(-1, -3), Angle()));

	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void RobotStateDriveToTest::isEquivalentToDriveTo_sameTarget_true()
{
	CPPUNIT_ASSERT(m_robotState->isEquivalentToDriveTo(Point(3, 2)));
}

void RobotStateDriveToTest::isEquivalentToDriveTo_differentTarget_true()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Point(5, 2)));
}