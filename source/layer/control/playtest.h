#ifndef ROBOSOCCER_LAYER_CONTROL_PLAYTEST_H
#define ROBOSOCCER_LAYER_CONTROL_PLAYTEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PlayTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PlayTest);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
	};
}
}
}

#endif


