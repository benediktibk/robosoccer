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
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
	};
}
}
}

#endif