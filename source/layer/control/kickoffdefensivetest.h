#ifndef ROBOSOCCER_LAYER_CONTROL_KICKOFFDEFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_KICKOFFDEFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class KickOffDefensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(KickOffDefensiveTest);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
	};
}
}
}

#endif


