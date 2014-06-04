#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATETURNTOTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATETURNTOTEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class RobotStateTurnToTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(RobotStateTurnToTest);
		CPPUNIT_TEST(reachedTarget_empty_false);
		CPPUNIT_TEST(cantReachTarget_empty_false);
		CPPUNIT_TEST(nextState_targetNotReached_0);
		CPPUNIT_TEST(nextState_targetReached_followingState);
		CPPUNIT_TEST(nextState_movementStopped_targetReachedState);
		CPPUNIT_TEST(update_empty_robotGotCallToTurnTo);
		CPPUNIT_TEST(update_targetOnTheAbove_robotGotCorrectAngleToTurnTo);
		CPPUNIT_TEST(update_targetOnTheLeft_robotGotCorrectAngleToTurnTo);
		CPPUNIT_TEST(update_twiceCalled_onlyOneCallToTurnTo);
		CPPUNIT_TEST(isEquivalentToDriveTo_empty_false);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void reachedTarget_empty_false();
		void cantReachTarget_empty_false();
		void nextState_targetNotReached_0();
		void nextState_targetReached_followingState();
		void nextState_movementStopped_targetReachedState();
		void update_empty_robotGotCallToTurnTo();
		void update_targetOnTheAbove_robotGotCorrectAngleToTurnTo();
		void update_targetOnTheLeft_robotGotCorrectAngleToTurnTo();
		void update_twiceCalled_onlyOneCallToTurnTo();
		void isEquivalentToDriveTo_empty_false();
	};
}
}
}

#endif


