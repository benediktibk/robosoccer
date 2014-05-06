#ifndef ROBOSOCCER_LAYER_ABSTRACTION_ROBOTDRIVECONTROLTEST_H
#define ROBOSOCCER_LAYER_ABSTRACTION_ROBOTDRIVECONTROLTEST_H

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
	class RobotDriveControl;

	class RobotDriveControlTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RobotDriveControlTest);
		CPPUNIT_TEST(evaluate_atTarget_bothValuesSmall);
		CPPUNIT_TEST(evaluate_farAwayFromTarget_bigSpeed);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void evaluate_atTarget_bothValuesSmall();
		void evaluate_farAwayFromTarget_bigSpeed();

	private:
		RobotDriveControl *m_control;
		Common::Time::WatchMock *m_watch;
	};
}
}
}

#endif