#include "layer/autonomous/robotstateturntotest.h"
#include "layer/autonomous/robotstateturnto.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotState *RobotStateTurnToTest::createInstance()
{
	return new RobotStateTurnTo(*m_controllableRobot, Point(0, 1), new RobotStateReachedTarget(*m_controllableRobot));
}

void RobotStateTurnToTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void RobotStateTurnToTest::cantReachTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->cantReachTarget());
}

void RobotStateTurnToTest::nextState_targetNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle(0)));

	RobotState *nextState = m_robotState->nextState();

	CPPUNIT_ASSERT(0 == nextState);
}

void RobotStateTurnToTest::nextState_targetReached_followingState()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));

	RobotState *nextState = m_robotState->nextState();

	RobotStateReachedTarget *nextStateCasted = dynamic_cast<RobotStateReachedTarget*>(nextState);
	CPPUNIT_ASSERT(0 != nextStateCasted);
	delete nextState;
}

void RobotStateTurnToTest::update_empty_robotGotCallToTurnTo()
{
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}