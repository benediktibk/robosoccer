#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOFINALROTATIONTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOFINALROTATIONTEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToFinalRotationTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(DriveToFinalRotationTest);
		CPPUNIT_TEST(constructor_routeWithTwoPoints_routeHasTwoPoints);
		CPPUNIT_TEST(update_onceCalled_robotGotOneCallToTurnToFinalRotation);
		CPPUNIT_TEST(update_twiceCalled_robotGotOneCallToTurnToFinalRotation);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void constructor_routeWithTwoPoints_routeHasTwoPoints();
		void update_onceCalled_robotGotOneCallToTurnToFinalRotation();
		void update_twiceCalled_robotGotOneCallToTurnToFinalRotation();
	};
}
}
}

#endif