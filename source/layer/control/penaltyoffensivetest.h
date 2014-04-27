#ifndef ROBOSOCCER_LAYER_CONTROL_PENALTYOFFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_PENALTYOFFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PenaltyOffensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PenaltyOffensiveTest);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
	};
}
}
}

#endif