#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETODIRECTDRIVINGTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETODIRECTDRIVINGTEST_H

#include "layer/autonomous/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class RobotStateDriveToDirectDrivingTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUB_SUITE(RobotStateDriveToDirectDrivingTest, RobotStateTest);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
	};
}
}
}

#endif