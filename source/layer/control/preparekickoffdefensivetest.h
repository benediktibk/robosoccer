#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFDEFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFDEFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PrepareKickOffDefensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PrepareKickOffDefensiveTest);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
	};
}
}
}

#endif


