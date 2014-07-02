#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISONEROBOTINSHOOTINGRANGE_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISONEROBOTINSHOOTINGRANGE_H

#include "layer/control/treenodedecider.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeDeciderIsOneRobotInShootingRange :
		public TreeNodeDecider
	{
	public:
		TreeNodeDeciderIsOneRobotInShootingRange(
				Common::Logging::Logger &logger, Abstraction::RefereeBase &referee,
				Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
				Autonomous::IntelligentBall const &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher,
				FollowBallRobot lastFollowBallRobot);

	private:
		virtual bool calculateDecision();


	};
}
}
}

#endif
