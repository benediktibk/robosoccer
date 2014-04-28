#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYOFFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYOFFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PreparePenaltyOffensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PreparePenaltyOffensiveTest);
		CPPUNIT_TEST(update_movementFinished_refereeGotCallToSetReady);
		CPPUNIT_TEST(nextState_movementFinished_penaltyOffensive);
		CPPUNIT_TEST(nextState_preparePenalty_0);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void update_movementFinished_refereeGotCallToSetReady();
		void nextState_movementFinished_penaltyOffensive();
		void nextState_preparePenalty_0();
	};
}
}
}

#endif