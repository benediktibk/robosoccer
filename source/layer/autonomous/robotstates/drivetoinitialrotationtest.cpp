#include "layer/autonomous/robotstates/drivetoinitialrotationtest.h"
#include "layer/autonomous/robotstates/drivetoinitialrotation.h"
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

RobotState *DriveToInitialRotationTest::createInstance()
{
	return new DriveToInitialRotation(
				*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
				*m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
				*m_autonomousRobotMock, false, false, false);
}

void DriveToInitialRotationTest::update_onceCalled_robotGotOneCallToTurnToSecondPoint()
{
	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(Point(0, 0), Point(5, 4)), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToInitialRotationTest::update_twiceCalled_robotGotOneCallToTurnToSecondPoint()
{
	m_robotState->update();
	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(Point(0, 0), Point(5, 4)), m_controllableRobot->getLastAngleToTurnTo()));
}
