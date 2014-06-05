#include "layer/autonomous/robotstates/drivetofinalrotationtest.h"
#include "layer/autonomous/robotstates/drivetofinalrotation.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/logging/loggermock.h"
#include "common/routing/routermock.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace std;

RobotState *DriveToFinalRotationTest::createInstance()
{
	return new DriveToFinalRotation(
				*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
				*m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
				*m_autonomousRobotMock, false, false, false, *m_route);
}

void DriveToFinalRotationTest::constructor_routeWithTwoPoints_routeHasTwoPoints()
{
	DriveToFinalRotation state(
					*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
					*m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
					*m_autonomousRobotMock, false, false, false, *m_route);

	CPPUNIT_ASSERT_EQUAL((size_t)2, state.getRoutePointsCount());
}

void DriveToFinalRotationTest::update_onceCalled_robotGotOneCallToTurnToFinalRotation()
{
	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToFinalRotationTest::update_twiceCalled_robotGotOneCallToTurnToFinalRotation()
{
	m_robotState->update();
	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}
