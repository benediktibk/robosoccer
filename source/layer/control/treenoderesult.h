#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODERESULT_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODERESULT_H

#include "layer/control/treenode.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeResult :
		public TreeNode
	{
	public:
		TreeNodeResult(
				Common::Logging::Logger &logger, Abstraction::RefereeBase &referee,
				Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
				Autonomous::IntelligentBall const &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher);

		virtual bool decide();
		virtual void execute() = 0;

	};
}
}
}

#endif


