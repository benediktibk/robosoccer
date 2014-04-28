#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYTEST_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYTEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PreparePenaltyTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PreparePenaltyTest);
		CPPUNIT_TEST(nextState_executePenalty_prepareState);
		CPPUNIT_TEST(nextState_hasPenalty_preparePenaltyOffensive);
		CPPUNIT_TEST(nextState_hasNotPenalty_preparePenaltyDefensive);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void nextState_executePenalty_prepareState();
		void nextState_hasPenalty_preparePenaltyOffensive();
		void nextState_hasNotPenalty_preparePenaltyDefensive();
	};
}
}
}

#endif


