#ifndef ROBOSOCCER_LAYER_CONTROL_KICKOFFOFFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_KICKOFFOFFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class KickOffOffensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(KickOffOffensiveTest);
		CPPUNIT_TEST(nextState_executeKickOff_0);
		CPPUNIT_TEST(nextState_continuePlaying_play);
		CPPUNIT_TEST(nextState_notExecuteKickOffAndNotContinuePlaying_pause);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void nextState_executeKickOff_0();
		void nextState_continuePlaying_play();
		void nextState_notExecuteKickOffAndNotContinuePlaying_pause();
		//! @todo test that one robot got a call to kick the ball
	};
}
}
}

#endif


