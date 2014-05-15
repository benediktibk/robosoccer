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
	class Router;
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
		CPPUNIT_TEST_SUITE(RobotStateTest);
		CPPUNIT_TEST(hasMovementStopped_stillMoving_false);
		CPPUNIT_TEST(hasMovementStopped_startedMovement_false);
		CPPUNIT_TEST(hasMovementStopped_stoppedMovement_true);
		CPPUNIT_TEST(hasMovementStopped_stillStopped_true);
		CPPUNIT_TEST(hasMovementStopped_onceAgainStarted_false);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	protected:
		virtual RobotState* createInstance();

	private:
		void hasMovementStopped_stillMoving_false();
		void hasMovementStopped_startedMovement_false();
		void hasMovementStopped_stoppedMovement_true();
		void hasMovementStopped_stillStopped_true();
		void hasMovementStopped_onceAgainStarted_false();

	protected:
		Abstraction::ControllableRobotMock *m_controllableRobot;
		Common::Time::WatchMock *m_watch;
		RobotState *m_robotState;
		Common::Logging::LoggerMock *m_logger;
		Common::Routing::Router *m_router;
	};
}
}
}

#endif
