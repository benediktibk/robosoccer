#include "layer/autonomous/robotstatedrivetotest.h"
#include "layer/autonomous/robotstatedriveto.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotState *RobotStateDriveToTest::createInstance()
{
	return new RobotStateDriveTo(*m_controllableRobot, Point(3, 2), true);
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

void RobotStateDriveToTest::update_precise_callToGoToPrecise()
{
	m_controllableRobot->setPose(Pose(Point(-1, -3), Angle()));

	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void RobotStateDriveToTest::update_imprecise_callToGoToPrecise()
{
	m_controllableRobot->setPose(Pose(Point(-1, -3), Angle()));
	RobotStateDriveTo robotState(*m_controllableRobot, Point(3, 2), false);

	robotState.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void RobotStateDriveToTest::isEquivalentToDriveTo_sameTarget_true()
{
	CPPUNIT_ASSERT(m_robotState->isEquivalentToDriveTo(Point(3, 2)));
}

void RobotStateDriveToTest::isEquivalentToDriveTo_differentTarget_true()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Point(5, 2)));
}