#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISINENEMYHALF_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISINENEMYHALF_H

#include "layer/control/treenodedecider.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeDeciderIsInEnemyHalf :
		public TreeNodeDecider
	{
	public:
		TreeNodeDeciderIsInEnemyHalf(
				Common::Logging::Logger &logger, Abstraction::RefereeBase &referee,
				Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
				Autonomous::IntelligentBall const &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher);

	private:
		virtual bool calculateDecision();


	};
}
}
}

#endif
