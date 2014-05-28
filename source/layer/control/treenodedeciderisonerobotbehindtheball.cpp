#include "layer/control/treenodedeciderisonerobotbehindtheball.h"
#include "layer/control/treenoderesultgetbehindball.h"
#include "layer/control/treenoderesultshoot.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"

using namespace RoboSoccer::Layer::Control;

TreeNodeDeciderIsOneRobotBehindTheBall::TreeNodeDeciderIsOneRobotBehindTheBall(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher) :
	TreeNodeDecider(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{ }

bool TreeNodeDeciderIsOneRobotBehindTheBall::calculateDecision()
{
	return true;
}
