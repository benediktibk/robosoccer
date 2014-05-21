#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYTEST_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYTEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class UserInputFetcherMock;

	class PreparePenaltyTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PreparePenaltyTest);
		CPPUNIT_TEST(nextState_executePenaltyButNoSelection_0);
		CPPUNIT_TEST(nextState_hasPenalty_preparePenaltyOffensive);
		CPPUNIT_TEST(nextState_hasNotPenalty_preparePenaltyDefensive);
		CPPUNIT_TEST(update_empty_oneCallToUpdateUserInputFetcher);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void tearDown();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
		void nextState_executePenaltyButNoSelection_0();
		void nextState_hasPenalty_preparePenaltyOffensive();
		void nextState_hasNotPenalty_preparePenaltyDefensive();
		void update_empty_oneCallToUpdateUserInputFetcher();

	private:
		UserInputFetcherMock *m_userInputFetcherMock;
	};
}
}
}

#endif