#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_REACHEDTARGETTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_REACHEDTARGETTEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class ReachedTargetTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(ReachedTargetTest);
		CPPUNIT_TEST(reachedTarget_empty_true);
		CPPUNIT_TEST(cantReachTarget_empty_false);
		CPPUNIT_TEST(nextState_empty_0);
		CPPUNIT_TEST(update_empty_callToStop);
		CPPUNIT_TEST(isEquivalentToDriveTo_differentPosition_false);
		CPPUNIT_TEST(isEquivalentToDriveTo_samePosition_true);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void reachedTarget_empty_true();
		void cantReachTarget_empty_false();
		void nextState_empty_0();
		void update_empty_callToStop();
		void isEquivalentToDriveTo_differentPosition_false();
		void isEquivalentToDriveTo_samePosition_true();
	};
}
}
}

#endif


