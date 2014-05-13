#include "layer/autonomous/robotstatedrivetodirecttest.h"
#include "layer/autonomous/robotstatedrivetodirect.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"
#include "common/geometry/pose.h"
#include "common/geometry/point.h"
#include "common/geometry/angle.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Geometry;

RobotState* RobotStateDriveToDirectTest::createInstance()
{
	return new RobotStateDriveToDirect(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()), *m_watch);
}

void RobotStateDriveToDirectTest::nextState_targetNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	RobotState *state = m_robotState->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void RobotStateDriveToDirectTest::nextState_targetReached_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getQuarterRotation()));

	RobotState *state = m_robotState->nextState();

	RobotStateReachedTarget *stateCasted = dynamic_cast<RobotStateReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void RobotStateDriveToDirectTest::nextState_longTimeWaited_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));
	m_watch->setTime(100);

	RobotState *state = m_robotState->nextState();

	RobotStateReachedTarget *stateCasted = dynamic_cast<RobotStateReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void RobotStateDriveToDirectTest::update_initialRotationNotReached_robotGotCallToTurnTowardsTarget()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update();

	Compare compare(0.0001);
	Angle targetShouldBe(Point(1, 2), Point(5, 4));
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(targetShouldBe, m_controllableRobot->getLastAngleToTurnTo()));
}

void RobotStateDriveToDirectTest::update_initialRotationNotReached_robotGotNoCallToDrive()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void RobotStateDriveToDirectTest::update_initialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void RobotStateDriveToDirectTest::update_positionNotReached_robotGotCallToDriveToTargetImprecise()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void RobotStateDriveToDirectTest::update_positionNotReached_robotGotNoCallToTurnTowardsTarget()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToTurn());
}

void RobotStateDriveToDirectTest::update_positionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void RobotStateDriveToDirectTest::update_finalRotationNotReached_robotGotCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void RobotStateDriveToDirectTest::update_finalRotationNotReached_robotGotNoCallToDrive()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void RobotStateDriveToDirectTest::update_finalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void RobotStateDriveToDirectTest::update_initialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void RobotStateDriveToDirectTest::update_positionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void RobotStateDriveToDirectTest::update_finalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void RobotStateDriveToDirectTest::isEquivalentToDriveTo_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Point(5, 4)));
}

void RobotStateDriveToDirectTest::isEquivalentToDriveToDirect_sameTarget_true()
{
	CPPUNIT_ASSERT(m_robotState->isEquivalentToDriveToDirect(Pose(Point(5, 4), Angle::getQuarterRotation())));
}

void RobotStateDriveToDirectTest::isEquivalentToDriveToDirect_differentTarget_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveToDirect(Pose(Point(5, 1), Angle::getQuarterRotation())));
}

void RobotStateDriveToDirectTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void RobotStateDriveToDirectTest::cantReachTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->cantReachTarget());
}
