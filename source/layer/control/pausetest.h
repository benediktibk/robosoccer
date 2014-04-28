#ifndef ROBOSOCCER_LAYER_CONTROL_PAUSETEST_H
#define ROBOSOCCER_LAYER_CONTROL_PAUSETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PauseTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PauseTest);
		CPPUNIT_TEST(nextState_prepareKickOffSet_prepareKickOff);
		CPPUNIT_TEST(nextState_gamePaused_0);
		CPPUNIT_TEST(nextState_preparePenaltySet_preparePenalty);
		CPPUNIT_TEST(nextState_continuePlayingSet_play);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void nextState_prepareKickOffSet_prepareKickOff();
		void nextState_gamePaused_0();
		void nextState_preparePenaltySet_preparePenalty();
		void nextState_continuePlayingSet_play();
	};
}
}
}

#endif


