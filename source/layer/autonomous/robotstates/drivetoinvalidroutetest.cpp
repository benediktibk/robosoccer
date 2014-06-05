#include "layer/autonomous/robotstates/drivetoinvalidroutetest.h"
#include "layer/autonomous/robotstates/drivetoinvalidroute.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/logging/loggermock.h"
#include "common/routing/routermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace std;

RobotState *DriveToInvalidRouteTest::createInstance()
{
	return new DriveToInvalidRoute(
				*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
				*m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
				*m_autonomousRobotMock, false, false, false);
}

void DriveToInvalidRouteTest::update_onceCalled_robotGotOneCallToStop()
{
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToStop());
}

void DriveToInvalidRouteTest::update_twiceCalled_robotGotTwoCallsToStop()
{
	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToStop());
}
