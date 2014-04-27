#ifndef ROBOSOCCER_LAYER_CONTROL_KICKOFFOFFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_KICKOFFOFFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class KickOffOffensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(KickOffOffensiveTest);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
	};
}
}
}

#endif


