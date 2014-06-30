#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODE_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODE_H

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
	class Logger;
}
}
namespace Layer
{
namespace Abstraction
{
	class RefereeBase;
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
class TreeNode
	{
	public:
		enum FollowBallRobot {
			FollowBallRobotNone,
			FollowBallRobotOne,
			FollowBallRobotTwo
		};

		TreeNode(
				Common::Logging::Logger &logger, Abstraction::RefereeBase &referee,
				Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
				Autonomous::IntelligentBall const &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher,
				FollowBallRobot lastFollowBallRobot);

		virtual ~TreeNode() { }
		virtual bool decide() = 0;

		FollowBallRobot getLastFollowBallRobot() const;

	protected:
		Common::Logging::Logger &m_logger;
		Abstraction::RefereeBase &m_referee;
		Autonomous::Team &m_ownTeam;
		const Autonomous::EnemyTeam &m_enemyTeam;
		const Autonomous::IntelligentBall &m_ball;
		const Autonomous::TargetPositionFetcher &m_targetPositionFetcher;
		FollowBallRobot m_lastFollowBallRobot;
	};
}
}
}

#endif
