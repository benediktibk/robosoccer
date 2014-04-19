#ifndef ROBOSOCCER_COMMON_STATES_STATEMACHINETEST_H
#define ROBOSOCCER_COMMON_STATES_STATEMACHINETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace States
{
	class StateMachineTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(StateMachineTest);
		CPPUNIT_TEST(update_empty_stateGotAtLeastOneCallToNextState);
		CPPUNIT_TEST(update_noStateChange_stateGotAtLeastOneCallToUpdate);
		CPPUNIT_TEST(update_stateChange_currentStateIsNewOne);
		CPPUNIT_TEST(update_stateChange_currentStateGotAtLeastOneCallToUpdate);
		CPPUNIT_TEST_SUITE_END();

	private:
		void update_empty_stateGotAtLeastOneCallToNextState();
		void update_noStateChange_stateGotAtLeastOneCallToUpdate();
		void update_stateChange_currentStateIsNewOne();
		void update_stateChange_currentStateGotAtLeastOneCallToUpdate();
	};
}
}
}

#endif
