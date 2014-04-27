#ifndef ROBOSOCCER_LAYER_CONTROL_PENALTYDEFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_PENALTYDEFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PenaltyDefensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PenaltyDefensiveTest);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
	};
}
}
}

#endif