#include "layer/autonomous/robotstates/robotstatetest.h"
#include "layer/autonomous/robotstates/robotstate.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "layer/abstraction/fieldpositioncheckermock.h"
#include "common/time/watchmock.h"
#include "common/logging/loggermock.h"
#include "common/routing/routermock.h"
#include "common/routing/route.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace RoboSoccer::Common::Geometry;

void RobotStateTest::setUp()
{
	m_ball = new IntelligentBallMock();
	m_controllableRobot = new ControllableRobotMock();
	m_watch = new WatchMock();
	m_logger = new LoggerMock();
	m_router = new RouterMock();
	m_obstacleFetcher = new ObstacleFetcherMock();
	m_autonomousRobotMock = new RobotMock();
	m_route = new Route(ControllableRobot::getWidth());
	m_route->addPoint(Point(0, 0));
	m_route->addPoint(Point(5, 4));
	m_fieldPositionChecker = new FieldPositionCheckerMock();
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
	delete m_logger;
	m_logger = 0;
	delete m_router;
	m_router = 0;
	delete m_obstacleFetcher;
	m_obstacleFetcher = 0;
	delete m_autonomousRobotMock;
	m_autonomousRobotMock = 0;
	delete m_ball;
	m_ball = 0;
	delete m_route;
	m_route = 0;
	delete m_fieldPositionChecker;
	m_fieldPositionChecker = 0;
}