#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDER_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDER_H

#include "layer/control/treenode.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeDecider :
		public TreeNode
	{
	public:
		TreeNodeDecider(
				Common::Logging::Logger &logger, Abstraction::RefereeBase &referee,
				Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
				Autonomous::IntelligentBall const &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher);

		virtual bool decide();
		virtual TreeNode* getChild();

	private:
		virtual bool calculateDecision() = 0;

	private:
		TreeNode *m_childYes;
		TreeNode *m_childNo;

	};
}
}
}

#endif


