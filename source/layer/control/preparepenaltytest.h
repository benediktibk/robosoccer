#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYTEST_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYTEST_H

#include "layer/control/robosoccerstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PreparePenaltyTest :
			public RoboSoccerStateTest
	{
		CPPUNIT_TEST_SUITE(PreparePenaltyTest);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RoboSoccerState* createInstance();

	private:
	};
}
}
}

#endif


