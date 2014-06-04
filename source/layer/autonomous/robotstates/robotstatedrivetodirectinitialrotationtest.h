#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATEDRIVETODIRECTINITIALROTATIONTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATEDRIVETODIRECTINITIALROTATIONTEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class RobotStateDriveToDirectInitialRotationTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(RobotStateDriveToDirectInitialRotationTest);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:

	};
}
}
}

#endif