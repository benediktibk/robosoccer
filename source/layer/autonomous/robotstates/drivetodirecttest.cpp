#include "layer/autonomous/robotstates/drivetodirecttest.h"
#include "layer/autonomous/robotstates/drivetodirect.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"
#include "common/geometry/pose.h"
#include "common/geometry/point.h"
#include "common/geometry/angle.h"
#include "common/geometry/compare.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotState* DriveToDirectTest::createInstance()
{
	return new DriveToDirect(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()), *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
}

void DriveToDirectTest::nextState_targetNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	RobotState *state = m_robotState->nextState(false);

	CPPUNIT_ASSERT(state == 0);
}

void DriveToDirectTest::nextState_targetReached_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getQuarterRotation()));

	RobotState *state = m_robotState->nextState(false);

	ReachedTarget *stateCasted = dynamic_cast<ReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToDirectTest::nextState_longTimeWaited_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));
	m_watch->setTime(100);

	RobotState *state = m_robotState->nextState(false);

	ReachedTarget *stateCasted = dynamic_cast<ReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToDirectTest::update_initialRotationNotReached_robotGotCallToTurnTowardsTarget()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update(false);

	Compare compare(0.0001);
	Angle targetShouldBe(Point(1, 2), Point(5, 4));
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(targetShouldBe, m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToDirectTest::update_initialRotationNotReached_robotGotNoCallToDrive()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void DriveToDirectTest::update_initialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void DriveToDirectTest::update_initialRotationNotReachedButMovementStopped_robotGotGallToDriveToTargetImprecise()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));
	m_robotState->update(false);
	m_robotState->update(false);
	m_robotState->update(true);

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void DriveToDirectTest::update_positionNotReached_robotGotCallToDriveToTargetImprecise()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update(false);

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void DriveToDirectTest::update_positionNotReached_robotGotNoCallToTurnTowardsTarget()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToTurn());
}

void DriveToDirectTest::update_positionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void DriveToDirectTest::update_positionNotreachedButMovementStopped_robotGotCallToTurnTo()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robotState->update(false);
	m_robotState->update(false);
	m_robotState->update(true);

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToDirectTest::update_finalRotationNotReached_robotGotCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update(false);

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToDirectTest::update_finalRotationNotReached_robotGotNoCallToDrive()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void DriveToDirectTest::update_finalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void DriveToDirectTest::update_finalRotationNotReachedButMovementStopped_nextStateWouldBeReachedTarget()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));
	m_robotState->update(false);
	m_robotState->update(false);
	m_robotState->update(true);

	RobotState *state = m_robotState->nextState(true);

	ReachedTarget *stateCasted = dynamic_cast<ReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToDirectTest::update_initialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void DriveToDirectTest::update_positionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void DriveToDirectTest::update_finalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void DriveToDirectTest::update_initalRotationReachedAndMovementStopped_robotGotCallToMove()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle()));
	m_robotState->update(false);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update(true);

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void DriveToDirectTest::update_positionReachedAndMovementStopped_robotGotCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robotState->update(false);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update(true);

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToDirectTest::isEquivalentToDriveTo_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Pose(Point(5, 4),Angle())));
}

void DriveToDirectTest::isEquivalentToDriveToDirect_sameTarget_true()
{
	CPPUNIT_ASSERT(m_robotState->isEquivalentToDriveToDirect(Pose(Point(5, 4), Angle::getQuarterRotation())));
}

void DriveToDirectTest::isEquivalentToDriveToDirect_differentTarget_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveToDirect(Pose(Point(5, 1), Angle::getQuarterRotation())));
}

void DriveToDirectTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}