#ifndef ROBOSOCCER_LAYER_CONTROL_PENALTYOFFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_PENALTYOFFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PenaltyOffensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PenaltyOffensiveTest);
		CPPUNIT_TEST(nextState_executePenalty_0);
		CPPUNIT_TEST(nextState_continuePlaying_play);
		CPPUNIT_TEST(nextState_notExecutePenaltyAndNotContinuePlaying_pause);
		CPPUNIT_TEST(update_onceCalled_noCallToKick);
		CPPUNIT_TEST(update_twiceCalled_noCallToKick);
		CPPUNIT_TEST(update_onceCalled_oneCallToMove);
		CPPUNIT_TEST(update_twiceCalled_oneCallToMove);
		CPPUNIT_TEST(update_twiceCalled_firstMoveThenKick);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void nextState_executePenalty_0();
		void nextState_continuePlaying_play();
		void nextState_notExecutePenaltyAndNotContinuePlaying_pause();
		void update_onceCalled_noCallToKick();
		void update_twiceCalled_noCallToKick();
		void update_onceCalled_oneCallToMove();
		void update_twiceCalled_oneCallToMove();
		void update_twiceCalled_firstMoveThenKick();
	};
}
}
}

#endif
