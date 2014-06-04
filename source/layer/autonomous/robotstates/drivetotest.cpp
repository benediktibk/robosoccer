#include "layer/autonomous/robotstates/drivetotest.h"
#include "layer/autonomous/robotstates/driveto.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"
#include "common/geometry/compare.h"
#include "common/logging/loggermock.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/autonomous/robotmock.h"
#include "common/routing/routerimpl.h"
#include "common/routing/fieldpositioncheckermock.h"
#include "layer/autonomous/robotstates/robotstate.h"
#include "common/routing/routermock.h"
#include <vector>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace std;

void DriveToTest::setUp()
{
	RobotStateTest::setUp();
	m_field = new FieldPositionCheckerMock();
	m_routerImpl = new RouterImpl(Abstraction::ReadableRobot::getWidth(), *m_field);
	m_robotStateWithRouter = new DriveTo(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
												   *m_routerImpl, *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
												   *m_obstacleFetcher, *m_autonomousRobotMock, false, false, false);
	m_robotStateWithRouterAndIgnoredBall =
			new DriveTo(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),	*m_routerImpl,
								  *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
								  *m_autonomousRobotMock, true, false, false);
	m_robotStateWithRouterAndDriveSlowlyAtTheEnd =
			new DriveTo(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),	*m_routerImpl,
								  *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
								  *m_autonomousRobotMock, false, true, false);
	m_robotStateWithRouterAndIgnoreGoalObstacles =
			new DriveTo(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),	*m_routerImpl,
								  *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
								  *m_autonomousRobotMock, false, false, true);
}

void DriveToTest::tearDown()
{
	RobotStateTest::tearDown();
	delete m_field;
	m_field = 0;
	delete m_routerImpl;
	m_routerImpl = 0;
	delete m_robotStateWithRouter;
	m_robotStateWithRouter = 0;
	delete m_robotStateWithRouterAndIgnoredBall;
	m_robotStateWithRouterAndIgnoredBall = 0;
	delete m_robotStateWithRouterAndDriveSlowlyAtTheEnd;
	m_robotStateWithRouterAndDriveSlowlyAtTheEnd = 0;
	delete m_robotStateWithRouterAndIgnoreGoalObstacles;
	m_robotStateWithRouterAndIgnoreGoalObstacles = 0;
}

RobotState *DriveToTest::createInstance()
{
	return new DriveTo(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),*m_router,
								 *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
								 *m_autonomousRobotMock, false, false, false);
}

void DriveToTest::nextState_targetNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	RobotState *state = m_robotState->nextState(false);

	CPPUNIT_ASSERT(state == 0);
}

void DriveToTest::nextState_targetReached_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getQuarterRotation()));

	RobotState *state = m_robotState->nextState(false);

	ReachedTarget *stateCasted = dynamic_cast<ReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToTest::nextState_longTimeWaited_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));
	m_watch->setTime(100);

	RobotState *state = m_robotState->nextState(false);

	ReachedTarget *stateCasted = dynamic_cast<ReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}


void DriveToTest::isEquivalentToDriveTo_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Pose(Point(5, 4),Angle())));
}

void DriveToTest::isEquivalentToDriveToDirect_sameTarget_true()
{
	CPPUNIT_ASSERT(m_robotState->isEquivalentToDriveTo(Pose(Point(5, 4), Angle::getQuarterRotation())));
}

void DriveToTest::isEquivalentToDriveToDirect_differentTarget_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Pose(Point(5, 1), Angle::getQuarterRotation())));
}

void DriveToTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void DriveToTest::cantReachTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->cantReachTarget());
}


void DriveToTest::nextState_thirdPositionReachedAndFinalRotationReached_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0,4),Angle::getEighthRotation()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0,4),Angle()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getEighthRotation()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_robotState->update(false);

	RobotState *state = m_robotState->nextState(false);

	ReachedTarget *stateCasted = dynamic_cast<ReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToTest::nextState_thirdPositionReachedAndFinalRotationReachedAndAllIntermediateMovementsStoppedByRobot_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update(false);
	m_robotState->update(false);
	m_robotState->update(true);
	m_robotState->update(false);
	m_robotState->update(true);
	m_robotState->update(false);
	m_robotState->update(true);
	m_robotState->update(false);
	m_robotState->update(true);
	m_robotState->update(false);
	m_robotState->update(true);

	RobotState *state = m_robotState->nextState(true);

	ReachedTarget *stateCasted = dynamic_cast<ReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}