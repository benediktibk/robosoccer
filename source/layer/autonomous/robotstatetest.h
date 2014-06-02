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
namespace Logging
{
	class LoggerMock;
}
namespace Routing
{
	class RouterMock;
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
	class ObstacleFetcherMock;
	class RobotMock;
	class IntelligentBallMock;

	class RobotStateTest :
			public CPPUNIT_NS::TestFixture
	{
	public:
		virtual void setUp();
		virtual void tearDown();

	protected:
		virtual RobotState* createInstance() = 0;

	private:

	protected:
		Abstraction::ControllableRobotMock *m_controllableRobot;
		Common::Time::WatchMock *m_watch;
		RobotState *m_robotState;
		Common::Logging::LoggerMock *m_logger;
		Common::Routing::RouterMock *m_router;
		ObstacleFetcherMock *m_obstacleFetcher;
		RobotMock *m_autonomousRobotMock;
		IntelligentBallMock *m_ball;
	};
}
}
}

#endif
