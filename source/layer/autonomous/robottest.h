#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTTEST_H

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
	class RobotImpl;
	class IntelligentBallMock;

	class RobotTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RobotTest);
		CPPUNIT_TEST(goTo_alreadyAtPosition_noCallToMoveRobot);
		CPPUNIT_TEST(goTo_notYetAtPosition_oneCallToMoveRobot);
		CPPUNIT_TEST(goTo_twiceWithSameTarget_oneCallToMoveRobot);
		CPPUNIT_TEST(goToDirect_alreadyAtPosition_noCallToMoveRobot);
		CPPUNIT_TEST(goToDirect_notYetAtPosition_oneCallToMoveRobot);
		CPPUNIT_TEST(goToDirect_twiceWithSameTarget_oneCallToMoveRobot);
		CPPUNIT_TEST(update_kickAndTurnToReachedTarget_oneCallToKick);
		CPPUNIT_TEST(update_empty_robotGotCallToUpdate);
		CPPUNIT_TEST(getObstacle_empty_sameAsFromControllableRobot);
		CPPUNIT_TEST(getObstacles_empty_oneWhichIsSameAsFromControllableRobot);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void goTo_alreadyAtPosition_noCallToMoveRobot();
		void goTo_notYetAtPosition_oneCallToMoveRobot();
		void goTo_twiceWithSameTarget_oneCallToMoveRobot();
		void goToDirect_alreadyAtPosition_noCallToMoveRobot();
		void goToDirect_notYetAtPosition_oneCallToMoveRobot();
		void goToDirect_twiceWithSameTarget_oneCallToMoveRobot();
		void update_kickAndTurnToReachedTarget_oneCallToKick();
		void update_empty_robotGotCallToUpdate();
		void getObstacle_empty_sameAsFromControllableRobot();
		void getObstacles_empty_oneWhichIsSameAsFromControllableRobot();

	private:
		Abstraction::ControllableRobotMock *m_hardwareRobot;
		Common::Time::WatchMock *m_watch;
		Common::Logging::LoggerMock *m_logger;
		Common::Routing::RouterMock *m_routerMock;
		RobotImpl *m_robot;
		IntelligentBallMock *m_ball;
	};
}
}
}

#endif
