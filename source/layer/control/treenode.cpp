#include "layer/control/treenode.h"

using namespace RoboSoccer::Layer::Control;

TreeNode::TreeNode(Common::Logging::Logger &logger, Abstraction::RefereeBase &referee,
		Autonomous::Team &ownTeam, const Autonomous::EnemyTeam &enemyTeam,
		const Autonomous::IntelligentBall &ball, const Autonomous::TargetPositionFetcher &targetPositionFetcher, FollowBallRobot lastFollowBallRobot) :
	m_logger(logger),
	m_referee(referee),
	m_ownTeam(ownTeam),
	m_enemyTeam(enemyTeam),
	m_ball(ball),
	m_targetPositionFetcher(targetPositionFetcher),
	m_lastFollowBallRobot(lastFollowBallRobot)
{ }

TreeNode::FollowBallRobot TreeNode::getLastFollowBallRobot() const
{
	return m_lastFollowBallRobot;
}
