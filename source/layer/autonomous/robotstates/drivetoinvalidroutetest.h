#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOINVALIDROUTETEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOINVALIDROUTETEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToInvalidRouteTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(DriveToInvalidRouteTest);
		CPPUNIT_TEST(update_onceCalled_robotGotOneCallToStop);
		CPPUNIT_TEST(update_twiceCalled_robotGotTwoCallsToStop);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void update_onceCalled_robotGotOneCallToStop();
		void update_twiceCalled_robotGotTwoCallsToStop();
	};
}
}
}

#endif


