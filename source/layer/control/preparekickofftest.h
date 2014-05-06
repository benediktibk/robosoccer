#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFTEST_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFTEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PrepareKickOffTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PrepareKickOffTest);
		CPPUNIT_TEST(nextState_executeKickOff_prepareState);
		CPPUNIT_TEST(nextState_hasKickOff_prepareKickOffOffensive);
		CPPUNIT_TEST(nextState_hasNotKickOff_prepareKickOffDefensive);
		CPPUNIT_TEST(update_onceCalled_noCallToKick);
		CPPUNIT_TEST(update_onceCalled_noCallToMove);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void nextState_executeKickOff_prepareState();
		void nextState_hasKickOff_prepareKickOffOffensive();
		void nextState_hasNotKickOff_prepareKickOffDefensive();
		void update_onceCalled_noCallToKick();
		void update_onceCalled_noCallToMove();
	};
}
}
}

#endif


