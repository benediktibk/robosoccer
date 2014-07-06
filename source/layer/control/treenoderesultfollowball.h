#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODERESULTFOLLOWBALL_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODERESULTFOLLOWBALL_H

#include "layer/control/treenoderesult.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeResultFollowBall :
		public TreeNodeResult
	{
	public:
		TreeNodeResultFollowBall(
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
