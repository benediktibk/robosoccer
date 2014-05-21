#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODETEST_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODETEST_H


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
	class BallMock;
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
class TreeNode;
class TreeNodeTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(TreeNodeTest);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	protected:
		virtual TreeNode* createTestNode() {return 0;}

	private:

	protected:
		TreeNode *m_node;
		Abstraction::RefereeMock *m_referee;
		Common::Logging::LoggerMock *m_logger;
		Autonomous::TeamMock *m_ownTeam;
		Autonomous::EnemyTeamMock *m_enemyTeam;
		Autonomous::IntelligentBallMock *m_ball;
		Autonomous::TargetPositionFetcher *m_targetPositionFetcher;
		Layer::Abstraction::BallMock *m_ballMock;
	};
}
}
}

#endif
