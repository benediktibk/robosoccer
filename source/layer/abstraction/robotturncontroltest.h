#ifndef ROBOSOCCER_LAYER_ABSTRACTION_ROBOTTURNCONTROLTEST_H
#define ROBOSOCCER_LAYER_ABSTRACTION_ROBOTTURNCONTROLTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
	class WatchMock;
}
}
namespace Layer
{
namespace Abstraction
{
	class RobotTurnControl;

	class RobotTurnControlTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RobotTurnControlTest);
		CPPUNIT_TEST(evaluate_mustTurnRight_negtiveResult);
		CPPUNIT_TEST(evaluate_mustTurnLeft_positiveResult);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void evaluate_mustTurnRight_negtiveResult();
		void evaluate_mustTurnLeft_positiveResult();

	private:
		RobotTurnControl *m_control;
		Common::Time::WatchMock *m_watch;
	};
}
}
}

#endif