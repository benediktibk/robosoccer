#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISONEROBOTBEHINDTHEBALL_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISONEROBOTBEHINDTHEBALL_H

#include "layer/control/treenodedecider.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeDeciderIsOneRobotBehindTheBall :
		public TreeNodeDecider
	{
	public:
		TreeNodeDeciderIsOneRobotBehindTheBall(
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
