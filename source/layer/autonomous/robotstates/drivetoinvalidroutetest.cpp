#include "layer/autonomous/robotstates/drivetoinvalidroutetest.h"
#include "layer/autonomous/robotstates/drivetoinvalidroute.h"
#include "layer/autonomous/robotstates/drivetoinitialrotation.h"
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
	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));

	return new DriveToInvalidRoute(
				*m_controllableRobot, targets, *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
				*m_obstacleFetcher,	*m_autonomousRobotMock, DriveMoveDefault);
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

void DriveToInvalidRouteTest::nextState_noRouteFeasible_0()
{
	m_router->setInvalidRoute();

	RobotState *nextState = m_robotState->nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void DriveToInvalidRouteTest::nextState_feasibleRoute_initialRotation()
{
	RobotState *nextState = m_robotState->nextState(false);

	DriveToInitialRotation *nextStateCasted = dynamic_cast<DriveToInitialRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToInvalidRouteTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}
