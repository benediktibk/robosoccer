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
		CPPUNIT_TEST(nextState_movementFinishedAndExecuteKickOff_kickOffDefensive);
		CPPUNIT_TEST(nextState_movementFinishedButNotExecuteKickOff_0);
		CPPUNIT_TEST(nextState_prepareKickOff_0);
		CPPUNIT_TEST(nextState_notPrepareKickOffAndNotExecuteKickOff_pause);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void update_movementFinished_refereeGotCallToSetReady();
		void nextState_movementFinishedAndExecuteKickOff_kickOffDefensive();
		void nextState_movementFinishedButNotExecuteKickOff_0();
		void nextState_prepareKickOff_0();
		void nextState_notPrepareKickOffAndNotExecuteKickOff_pause();
		//! @todo test that all robots got calls to move
		//! @todo test that the state waits till all movements are finished
	};
}
}
}

#endif


