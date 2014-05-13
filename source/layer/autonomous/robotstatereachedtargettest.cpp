#include "layer/autonomous/robotstatereachedtargettest.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotState *RobotStateReachedTargetTest::createInstance()
{
	return new RobotStateReachedTarget(*m_controllableRobot);
}

void RobotStateReachedTargetTest::reachedTarget_empty_true()
{
	CPPUNIT_ASSERT(m_robotState->reachedTarget());
}

void RobotStateReachedTargetTest::cantReachTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->cantReachTarget());
}

void RobotStateReachedTargetTest::nextState_empty_0()
{
	CPPUNIT_ASSERT(m_robotState->nextState() == 0);
}

void RobotStateReachedTargetTest::update_empty_callToStop()
{
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToStop());
}

void RobotStateReachedTargetTest::isEquivalentToDriveTo_differentPosition_false()
{
	m_controllableRobot->setPose(Pose(Point(4, 5), Angle()));

	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Pose(Point(3, 7),Angle())));
}

void RobotStateReachedTargetTest::isEquivalentToDriveTo_samePosition_true()
{
	m_controllableRobot->setPose(Pose(Point(4, 5), Angle()));

	CPPUNIT_ASSERT(m_robotState->isEquivalentToDriveTo(Pose(Point(4, 5),Angle())));
}
