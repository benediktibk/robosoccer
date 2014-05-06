#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TEAMTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TEAMTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
	class Logger;
}
namespace Time
{
	class Watch;
}
}
namespace Layer
{
namespace Abstraction
{
	class ControllableRobotMock;
	class StorageMock;
}
namespace Autonomous
{
	class TeamImpl;

	class TeamTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(TeamTest);
		CPPUNIT_TEST(getPlayerCloserToBall_playerOneCloser_correct);
		CPPUNIT_TEST(getPlayerFartherAwayFromBall_playerOneCloser_correct);
		CPPUNIT_TEST(getFirstFieldPlayer_empty_notTheGoalie);
		CPPUNIT_TEST(getSecondFieldPlayer_empty_notTheGoalie);
		CPPUNIT_TEST(getSecondFieldPlayer_empty_notTheFirstFieldPlayer);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void getPlayerCloserToBall_playerOneCloser_correct();
		void getPlayerFartherAwayFromBall_playerOneCloser_correct();
		void getFirstFieldPlayer_empty_notTheGoalie();
		void getSecondFieldPlayer_empty_notTheGoalie();
		void getSecondFieldPlayer_empty_notTheFirstFieldPlayer();

	private:
		TeamImpl *m_teamImpl;
		Abstraction::StorageMock *m_storageMock;
		Abstraction::ControllableRobotMock *m_controllableRobotMockGoalie;
		Abstraction::ControllableRobotMock *m_controllableRobotMockPlayer1;
		Abstraction::ControllableRobotMock *m_controllableRobotMockPlayer2;
		Common::Logging::Logger *m_loggerMock;
		Common::Time::Watch *m_watchMock;
	};
}
}
}

#endif


