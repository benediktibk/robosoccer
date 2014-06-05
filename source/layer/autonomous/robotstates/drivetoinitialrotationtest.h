#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOINITIALROTATIONTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOINITIALROTATIONTEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToInitialRotationTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(DriveToInitialRotationTest);
		CPPUNIT_TEST(update_onceCalled_robotGotOneCallToTurnToSecondPoint);
		CPPUNIT_TEST(update_twiceCalled_robotGotOneCallToTurnToSecondPoint);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void update_onceCalled_robotGotOneCallToTurnToSecondPoint();
		void update_twiceCalled_robotGotOneCallToTurnToSecondPoint();
	};
}
}
}

#endif