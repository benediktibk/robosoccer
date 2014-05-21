#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFOFFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFOFFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PrepareKickOffOffensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PrepareKickOffOffensiveTest);
		CPPUNIT_TEST(update_movementFinished_refereeGotCallToSetReady);
		CPPUNIT_TEST(update_movementNotYetStarted_allRobotsGotCallToMove);
		CPPUNIT_TEST(update_movementAlreadyStarted_allRobotsGotNoAdditonalCallToMove);
		CPPUNIT_TEST(update_movementNotYetFinished_refereeGotNoCallToSetReady);
		CPPUNIT_TEST(nextState_movementFinishedAndExecuteKickOff_kickOffOffensive);
		CPPUNIT_TEST(nextState_movementFinishedButNotExecuteKickOff_0);
		CPPUNIT_TEST(nextState_notPrepareKickOffAndNotExecuteKickOff_pause);
		CPPUNIT_TEST(nextState_movementOfOneRobotNotYetFinished_0);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void update_movementFinished_refereeGotCallToSetReady();
		void update_movementNotYetStarted_allRobotsGotCallToMove();
		void update_movementAlreadyStarted_allRobotsGotNoAdditonalCallToMove();
		void update_movementNotYetFinished_refereeGotNoCallToSetReady();
		void nextState_movementFinishedAndExecuteKickOff_kickOffOffensive();
		void nextState_movementFinishedButNotExecuteKickOff_0();
		void nextState_notPrepareKickOffAndNotExecuteKickOff_pause();
		void nextState_movementOfOneRobotNotYetFinished_0();
	};
}
}
}

#endif


