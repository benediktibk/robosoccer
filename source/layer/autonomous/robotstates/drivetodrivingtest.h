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
		CPPUNIT_TEST(nextState_targetReachedAndNoPointsLeft_finalRotation);
		CPPUNIT_TEST(nextState_movementStoppedAndNoPointsLeft_finalRotation);
		CPPUNIT_TEST(nextState_targetReachedAndRoutePointsLeft_initialRotationWithShorterRoute);
		CPPUNIT_TEST(nextState_movementStoppedAndRoutePointsLeft_initialRotationWithShorterRoute);
		CPPUNIT_TEST(nextState_obstacleBehindRobotOccurs_0);
		CPPUNIT_TEST(nextState_obstacleCloseToStartPositionAndTargetNotReached_0);
		CPPUNIT_TEST(reachedTarget_empty_false);
		CPPUNIT_TEST(nextState_targetNotReachedButProposalRouteIsMuchBetter_initialRotationWithNewRoute);
		CPPUNIT_TEST(nextState_targetNotReachedAndProposalRouteIsMuchBetterButInvalid_0);
		CPPUNIT_TEST(nextState_targetNotReachedAndProposalRouteIsMuchBetterButCurrentRouteIsToShort_0);
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
		void nextState_targetReachedAndNoPointsLeft_finalRotation();
		void nextState_movementStoppedAndNoPointsLeft_finalRotation();
		void nextState_targetReachedAndRoutePointsLeft_initialRotationWithShorterRoute();
		void nextState_movementStoppedAndRoutePointsLeft_initialRotationWithShorterRoute();
		void nextState_obstacleBehindRobotOccurs_0();
		void nextState_obstacleCloseToStartPositionAndTargetNotReached_0();
		void reachedTarget_empty_false();
		void nextState_targetNotReachedButProposalRouteIsMuchBetter_initialRotationWithNewRoute();
		void nextState_targetNotReachedAndProposalRouteIsMuchBetterButInvalid_0();
		void nextState_targetNotReachedAndProposalRouteIsMuchBetterButCurrentRouteIsToShort_0();
	};
}
}
}

#endif
