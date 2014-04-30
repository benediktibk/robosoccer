#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATETEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATETEST_H

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
	class ControllableRobotMock;
}
namespace Autonomous
{
	class RobotState;

	class RobotStateTest :
			public CPPUNIT_NS::TestFixture
	{
	public:
		virtual void setUp();
		virtual void tearDown();

	protected:
		virtual RobotState* createInstance() = 0;

	protected:
		Abstraction::ControllableRobotMock *m_controllableRobot;
		Common::Time::WatchMock *m_watch;
		RobotState *m_robotState;
	};
}
}
}

#endif