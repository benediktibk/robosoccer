#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFDEFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFDEFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PrepareKickOffDefensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PrepareKickOffDefensiveTest);
		CPPUNIT_TEST(update_movementFinished_refereeGotCallToSetReady);
		CPPUNIT_TEST(nextState_movementFinished_kickOffDefensive);
		CPPUNIT_TEST(nextState_prepareKickOff_0);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void update_movementFinished_refereeGotCallToSetReady();
		void nextState_movementFinished_kickOffDefensive();
		void nextState_prepareKickOff_0();
	};
}
}
}

#endif


