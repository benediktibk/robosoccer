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
		CPPUNIT_TEST(update_movementNotYetStarted_allRobotsGotCallToMove);
		CPPUNIT_TEST(update_movementAlreadyStarted_allRobotsGotNoAdditionalCallToMove);
		CPPUNIT_TEST(update_movementNotYetFinished_refereeGotNoCallToSetReady);
		CPPUNIT_TEST(nextState_movementFinishedAndExecuteKickOff_kickOffDefensive);
		CPPUNIT_TEST(nextState_movementFinishedButNotExecuteKickOff_0);
		CPPUNIT_TEST(nextState_notPrepareKickOffAndNotExecuteKickOff_pause);
		CPPUNIT_TEST(nextState_movementOfOneRobotNotYetFinished_0);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void update_movementFinished_refereeGotCallToSetReady();
		void update_movementNotYetStarted_allRobotsGotCallToMove();
		void update_movementAlreadyStarted_allRobotsGotNoAdditionalCallToMove();
		void update_movementNotYetFinished_refereeGotNoCallToSetReady();
		void nextState_movementFinishedAndExecuteKickOff_kickOffDefensive();
		void nextState_movementFinishedButNotExecuteKickOff_0();
		void nextState_notPrepareKickOffAndNotExecuteKickOff_pause();
		void nextState_movementOfOneRobotNotYetFinished_0();
	};
}
}
}

#endif


