#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEREACHEDTARGETTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEREACHEDTARGETTEST_H

#include "layer/autonomous/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class RobotStateReachedTargetTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(RobotStateReachedTargetTest);
		CPPUNIT_TEST(reachedTarget_empty_true);
		CPPUNIT_TEST(cantReachTarget_empty_false);
		CPPUNIT_TEST(nextState_empty_0);
		CPPUNIT_TEST(update_empty_callToStop);
		CPPUNIT_TEST(isEquivalentToDriveTo_empty_false);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void reachedTarget_empty_true();
		void cantReachTarget_empty_false();
		void nextState_empty_0();
		void update_empty_callToStop();
		void isEquivalentToDriveTo_empty_false();
	};
}
}
}

#endif


