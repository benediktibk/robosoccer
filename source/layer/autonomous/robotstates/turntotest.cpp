#include "layer/autonomous/robotstates/turntotest.h"
#include "layer/autonomous/robotstates/turnto.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/geometry/compare.h"
#include "common/time/watchmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

RobotState *TurnToTest::createInstance()
{
	return new TurnTo(*m_controllableRobot, Point(0, 1), new ReachedTarget(*m_controllableRobot, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie), *m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
}

void TurnToTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void TurnToTest::nextState_targetNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle(0)));

	RobotState *nextState = m_robotState->nextState(false);

	CPPUNIT_ASSERT(0 == nextState);
}

void TurnToTest::nextState_targetReached_followingState()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));

	RobotState *nextState = m_robotState->nextState(false);

	ReachedTarget *nextStateCasted = dynamic_cast<ReachedTarget*>(nextState);
	CPPUNIT_ASSERT(0 != nextStateCasted);
	delete nextState;
}

void TurnToTest::nextState_movementStopped_targetReachedState()
{
	m_robotState->update();
	m_robotState->update();
	m_robotState->update();

	RobotState *nextState = m_robotState->nextState(true);

	ReachedTarget *nextStateCasted = dynamic_cast<ReachedTarget*>(nextState);
	CPPUNIT_ASSERT(0 != nextStateCasted);
	delete nextState;
}

void TurnToTest::update_empty_robotGotCallToTurnTo()
{
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void TurnToTest::update_targetOnTheAbove_robotGotCorrectAngleToTurnTo()
{
	m_controllableRobot->setPose(Pose(Point(1, 1), Angle()));

	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void TurnToTest::update_targetOnTheLeft_robotGotCorrectAngleToTurnTo()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle()));

	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void TurnToTest::update_twiceCalled_onlyOneCallToTurnTo()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle()));

	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void TurnToTest::isEquivalentToDriveTo_empty_false()
{
	vector<Pose> pose;
	pose.push_back(Pose());

	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(pose));
}
