#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODERESULTGETBEHINDBALL_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODERESULTGETBEHINDBALL_H

#include "layer/control/treenoderesult.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeResultGetBehindBall :
		public TreeNodeResult
	{
	public:
		TreeNodeResultGetBehindBall(
				Common::Logging::Logger &logger, Abstraction::RefereeBase &referee,
				Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
				Autonomous::IntelligentBall const &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher,
				FollowBallRobot lastFollowBallRobot);

		virtual void execute();


	};
}
}
}

#endif
