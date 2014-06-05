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
		CPPUNIT_TEST(constructor_routeWithThreePoints_routesHasThreePoints);
		CPPUNIT_TEST(update_onceCalled_robotGotOneCallToGoToSecondPoint);
		CPPUNIT_TEST(update_twiceCalled_robotGotOneCallToGoToSecondPoint);
		CPPUNIT_TEST(nextState_routeBecomesInvalidAndNoNewOnePossible_invalidRoute);
		CPPUNIT_TEST(nextState_routeBecomesInvalidAndNewOnePossible_initialRotation);
		CPPUNIT_TEST(nextState_targetNotReached_0);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void constructor_routeWithThreePoints_routesHasThreePoints();
		void update_onceCalled_robotGotOneCallToGoToSecondPoint();
		void update_twiceCalled_robotGotOneCallToGoToSecondPoint();
		void nextState_routeBecomesInvalidAndNoNewOnePossible_invalidRoute();
		void nextState_routeBecomesInvalidAndNewOnePossible_initialRotation();
		void nextState_targetNotReached_0();
	};
}
}
}

#endif