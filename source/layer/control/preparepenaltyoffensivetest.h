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
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
	};
}
}
}

#endif