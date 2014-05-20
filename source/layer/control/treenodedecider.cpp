#include "layer/control/treenodedecider.h"

using namespace RoboSoccer::Layer::Control;

TreeNodeDecider::TreeNodeDecider(
		Common::Logging::Logger &logger, Abstraction::RefereeBase &referee,
		Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
		Autonomous::IntelligentBall const &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher) :
	TreeNode(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{ }

bool TreeNodeDecider::decide()
{
	return true;
}

TreeNode *TreeNodeDecider::getChild()
{
	if(calculateDecision())
	{
		delete m_childNo;
		m_childNo = 0;
		return m_childYes;
	}
	else
	{
		delete m_childYes;
		m_childYes = 0;
		return m_childNo;
	}

	return 0;
}
