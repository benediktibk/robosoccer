#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECTDRIVINGTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECTDRIVINGTEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToDirectDrivingTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(DriveToDirectDrivingTest);
		CPPUNIT_TEST(reachedTarget_empty_false);
		CPPUNIT_TEST(update_onceCalled_robotGotOneCallToDriveToTarget);
		CPPUNIT_TEST(update_twiceCalled_robotGotOneCallToDriveToTarget);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void reachedTarget_empty_false();
		void update_onceCalled_robotGotOneCallToDriveToTarget();
		void update_twiceCalled_robotGotOneCallToDriveToTarget();
	};
}
}
}

#endif