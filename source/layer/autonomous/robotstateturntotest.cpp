#include "layer/autonomous/robotstateturntotest.h"
#include "layer/autonomous/robotstateturnto.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/geometry/compare.h"
#include "common/time/watchmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotState *RobotStateTurnToTest::createInstance()
{
	return new RobotStateTurnTo(*m_controllableRobot, Point(0, 1), *m_watch, new RobotStateReachedTarget(*m_controllableRobot, *m_logger), *m_logger);
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

void RobotStateTurnToTest::nextState_took10s_targetReachedState()
{
	m_watch->setTime(10);

	RobotState *nextState = m_robotState->nextState();

	RobotStateReachedTarget *nextStateCasted = dynamic_cast<RobotStateReachedTarget*>(nextState);
	CPPUNIT_ASSERT(0 != nextStateCasted);
	delete nextState;
}

void RobotStateTurnToTest::nextState_took10sWithSeveralCalls_targetReachedState()
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

void RobotStateTurnToTest::update_empty_robotGotCallToTurnTo()
{
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void RobotStateTurnToTest::update_targetOnTheAbove_robotGotCorrectAngleToTurnTo()
{
	m_controllableRobot->setPose(Pose(Point(1, 1), Angle()));

	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void RobotStateTurnToTest::update_targetOnTheLeft_robotGotCorrectAngleToTurnTo()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle()));

	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void RobotStateTurnToTest::update_twiceCalled_onlyOneCallToTurnTo()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle()));

	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void RobotStateTurnToTest::isEquivalentToDriveTo_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Pose()));
}
