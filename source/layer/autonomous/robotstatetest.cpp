#include "layer/autonomous/robotstatetest.h"
#include "layer/autonomous/robotstate.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Time;

void RobotStateTest::setUp()
{
	m_controllableRobot = new ControllableRobotMock();
	m_watch = new WatchMock();
	m_robotState = createInstance();
	assert(m_robotState != 0);
}

void RobotStateTest::tearDown()
{
	delete m_robotState;
	m_robotState = 0;
	delete m_controllableRobot;
	m_controllableRobot = 0;
	delete m_watch;
	m_watch = 0;
}

RobotState *RobotStateTest::createInstance()
{
	return 0;
}

void RobotStateTest::hasMovementStopped_stillMoving_false()
{
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();

	bool movementStopped = m_robotState->hasMovementStopped();

	CPPUNIT_ASSERT(!movementStopped);
}

void RobotStateTest::hasMovementStopped_startedMovement_false()
{
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();

	bool movementStopped = m_robotState->hasMovementStopped();

	CPPUNIT_ASSERT(!movementStopped);
}

void RobotStateTest::hasMovementStopped_stoppedMovement_true()
{
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();

	bool movementStopped = m_robotState->hasMovementStopped();

	CPPUNIT_ASSERT(movementStopped);
}

void RobotStateTest::hasMovementStopped_stillStopped_true()
{
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();

	bool movementStopped = m_robotState->hasMovementStopped();

	CPPUNIT_ASSERT(movementStopped);
}

void RobotStateTest::hasMovementStopped_onceAgainStarted_false()
{
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();

	bool movementStopped = m_robotState->hasMovementStopped();

	CPPUNIT_ASSERT(!movementStopped);
}