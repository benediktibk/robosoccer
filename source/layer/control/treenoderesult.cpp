#include "layer/control/treenoderesult.h"

using namespace RoboSoccer::Layer::Control;

TreeNodeResult::TreeNodeResult(RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher, FollowBallRobot lastFollowBallRobot) :
	TreeNode(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, lastFollowBallRobot)
{ }

bool TreeNodeResult::decide()
{
	return false;
}
