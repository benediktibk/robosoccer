#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODERESULTDEFENDGOAL_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODERESULTDEFENDGOAL_H

#include "layer/control/treenoderesult.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeResultDefendGoal :
		public TreeNodeResult
	{
	public:
		TreeNodeResultDefendGoal(
				Common::Logging::Logger &logger, Abstraction::RefereeBase &referee,
				Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
				Autonomous::IntelligentBall const &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher);

		virtual void execute();


	};
}
}
}

#endif
