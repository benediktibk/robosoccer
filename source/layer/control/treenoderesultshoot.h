#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODERESULTSHOOT_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODERESULTSHOOT_H

#include "layer/control/treenoderesult.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeResultShoot :
		public TreeNodeResult
	{
	public:
		TreeNodeResultShoot(
				Common::Logging::Logger &logger, Abstraction::RefereeBase &referee,
				Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
				Autonomous::IntelligentBall const &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher);

		virtual void execute();


	};
}
}
}

#endif