#include "layer/autonomous/robotstatetest.h"
#include "layer/autonomous/robotstate.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Time;

void RobotStateTest::setUp()
{
	m_controllableRobot = new ControllableRobotMock();
	m_watch = new WatchMock();
	m_robotState = createInstance();
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