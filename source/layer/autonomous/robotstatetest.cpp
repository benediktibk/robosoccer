#include "layer/autonomous/robotstatetest.h"
#include "layer/autonomous/robotstate.h"
#include "layer/abstraction/controllablerobotmock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;

void RobotStateTest::setUp()
{
	m_controllableRobot = new ControllableRobotMock();
	m_robotState = createInstance();
}

void RobotStateTest::tearDown()
{
	delete m_robotState;
	m_robotState = 0;
	delete m_controllableRobot;
	m_controllableRobot = 0;
}