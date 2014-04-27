#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFTEST_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFTEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PrepareKickOffTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PrepareKickOffTest);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
	};
}
}
}

#endif


