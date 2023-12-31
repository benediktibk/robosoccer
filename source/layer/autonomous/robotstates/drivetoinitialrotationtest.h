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
		CPPUNIT_TEST(nextState_routeBecomesInvalidAndNoNewOnePossible_invalidRoute);
		CPPUNIT_TEST(nextState_routeBecomesInvalidAndNewOnePossible_initialRotation);
		CPPUNIT_TEST(nextState_targetNotReached_0);
		CPPUNIT_TEST(nextState_movementStopped_driving);
		CPPUNIT_TEST(nextState_targetReached_driving);
		CPPUNIT_TEST(constructor_noRoute_routeCreated);
		CPPUNIT_TEST(constructor_routeWithThreePoints_routeHasThreePoints);
		CPPUNIT_TEST(reachedTarget_empty_false);
		CPPUNIT_TEST(constructor_noRouteAndFirstRouteInvalid_routeCreated);
		CPPUNIT_TEST(nextState_targetNotReachedButProposalRouteIsMuchBetter_initialRotationWithNewRoute);
		CPPUNIT_TEST(nextState_targetNotReachedAndProposalRouteIsMuchBetterButInvalid_0);
		CPPUNIT_TEST(nextState_targetNotReachedAndProposalRouteIsMuchBetterButCurrentRouteIsToShort_0);
		CPPUNIT_TEST(nextState_currentRouteNotFeasibleAndNextOneToo_invalidRoute);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void update_onceCalled_robotGotOneCallToTurnToSecondPoint();
		void update_twiceCalled_robotGotOneCallToTurnToSecondPoint();
		void nextState_routeBecomesInvalidAndNoNewOnePossible_invalidRoute();
		void nextState_routeBecomesInvalidAndNewOnePossible_initialRotation();
		void nextState_targetNotReached_0();
		void nextState_movementStopped_driving();
		void nextState_targetReached_driving();
		void constructor_noRoute_routeCreated();
		void constructor_routeWithThreePoints_routeHasThreePoints();
		void reachedTarget_empty_false();
		void constructor_noRouteAndFirstRouteInvalid_routeCreated();
		void nextState_targetNotReachedButProposalRouteIsMuchBetter_initialRotationWithNewRoute();
		void nextState_targetNotReachedAndProposalRouteIsMuchBetterButInvalid_0();
		void nextState_targetNotReachedAndProposalRouteIsMuchBetterButCurrentRouteIsToShort_0();
		void nextState_currentRouteNotFeasibleAndNextOneToo_invalidRoute();
	};
}
}
}

#endif
