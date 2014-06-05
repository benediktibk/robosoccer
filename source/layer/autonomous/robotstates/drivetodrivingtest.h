#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODRIVINGTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODRIVINGTEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToDrivingTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(DriveToDrivingTest);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:

	};
}
}
}

#endif