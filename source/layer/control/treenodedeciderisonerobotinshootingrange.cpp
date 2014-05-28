#include "layer/control/treenodedeciderisonerobotinshootingrange.h"
#include "layer/control/treenoderesultdefendgoal.h"
#include "layer/control/treenoderesultattackball.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"

using namespace RoboSoccer::Layer::Control;

TreeNodeDeciderIsOneRobotInShootingRange::TreeNodeDeciderIsOneRobotInShootingRange(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher) :
	TreeNodeDecider(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{ }

bool TreeNodeDeciderIsOneRobotInShootingRange::calculateDecision()
{
	return true;
}
