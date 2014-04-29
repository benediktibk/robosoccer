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
	class EnemyTeam;
	class Team;
	class IntelligentBall;
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
		Abstraction::StorageMock *m_storage;
		Autonomous::Team *m_ownTeam;
		Autonomous::EnemyTeam *m_enemyTeam;
		Autonomous::IntelligentBall *m_ball;
		Autonomous::TargetPositionFetcher *m_targetPositionFetcher;
	};
}
}
}

#endif


