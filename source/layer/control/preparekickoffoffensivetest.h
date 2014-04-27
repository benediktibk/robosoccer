#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFOFFENSIVETEST_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFOFFENSIVETEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PrepareKickOffOffensiveTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PrepareKickOffOffensiveTest);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
	};
}
}
}

#endif


