#ifndef ROBOSOCCER_LAYER_CONTROL_PENALTYDEFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_PENALTYDEFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PenaltyDefensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PenaltyDefensiveTest);
		CPPUNIT_TEST(nextState_executePenalty_0);
		CPPUNIT_TEST(nextState_continuePlaying_play);
		CPPUNIT_TEST(nextState_notExecutePenaltyAndNotContinuePlaying_pause);
		CPPUNIT_TEST(update_robotInsideGoalzone_oneRobotGotCallToGoToDirect);
		CPPUNIT_TEST(update_robotInsideGoalzoneAndUpdateTwiceCalled_twoCallsToGoToDirect);
		CPPUNIT_TEST(update_robotNotInsideGoalZone_callToGoTo);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void nextState_executePenalty_0();
		void nextState_continuePlaying_play();
		void nextState_notExecutePenaltyAndNotContinuePlaying_pause();
		void update_robotInsideGoalzone_oneRobotGotCallToGoToDirect();
		void update_robotInsideGoalzoneAndUpdateTwiceCalled_twoCallsToGoToDirect();
		void update_robotNotInsideGoalZone_callToGoTo();
	};
}
}
}

#endif
