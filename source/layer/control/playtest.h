#ifndef ROBOSOCCER_LAYER_CONTROL_PLAYTEST_H
#define ROBOSOCCER_LAYER_CONTROL_PLAYTEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PlayTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PlayTest);
		CPPUNIT_TEST(nextState_everythingSet_0);
		CPPUNIT_TEST(nextState_notContinuePlaying_pause);
		CPPUNIT_TEST(update_ballInDangerZone_goalieGotCallToStop);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void nextState_everythingSet_0();
		void nextState_notContinuePlaying_pause();
		void update_ballInDangerZone_goalieGotCallToStop();
	};
}
}
}

#endif
