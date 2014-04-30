#ifndef ROBOSOCCER_LAYER_CONTROL_ROBOSOCCERSTATETEST_H
#define ROBOSOCCER_LAYER_CONTROL_ROBOSOCCERSTATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
	class LoggerMock;
}
namespace Time
{
	class WatchMock;
}
}
namespace Layer
{
namespace Abstraction
{
	class RefereeMock;
	class StorageMock;
}
namespace Autonomous
{
	class EnemyTeamMock;
	class TeamMock;
	class IntelligentBallMock;
	class TargetPositionFetcher;
}

namespace Control
{
	class RoboSoccerState;

	class RoboSoccerStateTest :
			public CPPUNIT_NS::TestFixture
	{
	public:
		virtual void setUp();
		virtual void tearDown();

	protected:
		virtual RoboSoccerState* createInstance() = 0;

	protected:
		RoboSoccerState *m_state;
		Abstraction::RefereeMock *m_referee;
		Common::Logging::LoggerMock *m_logger;
		Autonomous::TeamMock *m_ownTeam;
		Autonomous::EnemyTeamMock *m_enemyTeam;
		Autonomous::IntelligentBallMock *m_ball;
		Autonomous::TargetPositionFetcher *m_targetPositionFetcher;
	};
}
}
}

#endif


