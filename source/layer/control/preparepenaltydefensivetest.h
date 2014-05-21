#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYDEFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYDEFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PreparePenaltyDefensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PreparePenaltyDefensiveTest);
		CPPUNIT_TEST(update_movementFinished_refereeGotCallToSetReady);
		CPPUNIT_TEST(update_movementNotYetStarted_allRobotsGotCallToMove);
		CPPUNIT_TEST(update_movementAlreadyStarted_allRobotsGotNoAdditionalCallToMove);
		CPPUNIT_TEST(update_movementNotYetFinished_refereeGotNoCallToSetReady);
		CPPUNIT_TEST(nextState_movementFinishedAndExecutePenalty_penaltyDefensive);
		CPPUNIT_TEST(nextState_movementFinishedButNotExecutePenalty_0);
		CPPUNIT_TEST(nextState_preparePenalty_0);
		CPPUNIT_TEST(nextState_notPreparePenaltyAndNotExecutePenalty_pause);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void update_movementFinished_refereeGotCallToSetReady();
		void update_movementNotYetStarted_allRobotsGotCallToMove();
		void update_movementAlreadyStarted_allRobotsGotNoAdditionalCallToMove();
		void update_movementNotYetFinished_refereeGotNoCallToSetReady();
		void nextState_movementFinishedAndExecutePenalty_penaltyDefensive();
		void nextState_movementFinishedButNotExecutePenalty_0();
		void nextState_preparePenalty_0();
		void nextState_notPreparePenaltyAndNotExecutePenalty_pause();
		void nextState_movementOfOneRobotNotYetFinished_0();
	};
}
}
}

#endif