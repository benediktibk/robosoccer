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
		CPPUNIT_TEST(update_movementNotYetStarted_allRobotsGotCallToMove);
		CPPUNIT_TEST(update_movementAlreadyStarted_allRobotsGotNoAdditionalCallToMove);
		CPPUNIT_TEST(update_movementNotYetFinished_refereeGotNoCallToSetReady);
		CPPUNIT_TEST(nextState_movementFinishedAndExecutePenalty_penaltyOffensive);
		CPPUNIT_TEST(nextState_movementFinishedButNotExecutePenalty_0);
		CPPUNIT_TEST(nextState_notPreparePenaltyAndNotExecutePenalty_pause);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void update_movementFinished_refereeGotCallToSetReady();
		void update_movementNotYetStarted_allRobotsGotCallToMove();
		void update_movementAlreadyStarted_allRobotsGotNoAdditionalCallToMove();
		void update_movementNotYetFinished_refereeGotNoCallToSetReady();
		void nextState_movementFinishedAndExecutePenalty_penaltyOffensive();
		void nextState_movementFinishedButNotExecutePenalty_0();
		void nextState_notPreparePenaltyAndNotExecutePenalty_pause();
		void nextState_movementOfOneRobotNotYetFinished_0();
	};
}
}
}

#endif