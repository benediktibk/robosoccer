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
		CPPUNIT_TEST(nextState_movementFinishedAndExecutePenalty_penaltyDefensive);
		CPPUNIT_TEST(nextState_movementFinishedButNotExecutePenalty_0);
		CPPUNIT_TEST(nextState_preparePenalty_0);
		CPPUNIT_TEST(nextState_notPreparePenaltyAndNotExecutePenalty_pause);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void update_movementFinished_refereeGotCallToSetReady();
		void nextState_movementFinishedAndExecutePenalty_penaltyDefensive();
		void nextState_movementFinishedButNotExecutePenalty_0();
		void nextState_preparePenalty_0();
		void nextState_notPreparePenaltyAndNotExecutePenalty_pause();
		//! @todo test that all robots got calls to move
		//! @todo test that the state waits till all movements are finished
	};
}
}
}

#endif