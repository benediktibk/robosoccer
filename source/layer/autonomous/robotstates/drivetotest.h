#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOTEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Common
{
namespace Routing
{
	class RouterImpl;
	class FieldPositionCheckerMock;
}
}
namespace Layer
{
namespace Autonomous
{
	class RobotState;
	class DriveTo;

	class DriveToTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(DriveToTest);
		CPPUNIT_TEST(nextState_targetNotReached_0);
		CPPUNIT_TEST(nextState_targetReached_reachedTargetState);
		CPPUNIT_TEST(nextState_longTimeWaited_reachedTargetState);
		CPPUNIT_TEST(isEquivalentToDriveTo_empty_false);
		CPPUNIT_TEST(isEquivalentToDriveToDirect_sameTarget_true);
		CPPUNIT_TEST(isEquivalentToDriveToDirect_differentTarget_false);
		CPPUNIT_TEST(reachedTarget_empty_false);
		CPPUNIT_TEST(nextState_thirdPositionReachedAndFinalRotationReached_reachedTargetState);
		CPPUNIT_TEST(nextState_thirdPositionReachedAndFinalRotationReachedAndAllIntermediateMovementsStoppedByRobot_reachedTargetState);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	protected:
		virtual RobotState* createInstance();

	private:
		void nextState_targetNotReached_0();
		void nextState_targetReached_reachedTargetState();
		void nextState_longTimeWaited_reachedTargetState();
		void isEquivalentToDriveTo_empty_false();
		void isEquivalentToDriveToDirect_sameTarget_true();
		void isEquivalentToDriveToDirect_differentTarget_false();
		void reachedTarget_empty_false();
		void nextState_thirdPositionReachedAndFinalRotationReached_reachedTargetState();
		void nextState_thirdPositionReachedAndFinalRotationReachedAndAllIntermediateMovementsStoppedByRobot_reachedTargetState();

	private:
		DriveTo *m_robotStateWithRouter;
		DriveTo *m_robotStateWithRouterAndIgnoredBall;
		DriveTo *m_robotStateWithRouterAndDriveSlowlyAtTheEnd;
		DriveTo *m_robotStateWithRouterAndIgnoreGoalObstacles;
		Common::Routing::RouterImpl *m_routerImpl;
		Common::Routing::FieldPositionCheckerMock *m_field;
	};
}
}
}

#endif


