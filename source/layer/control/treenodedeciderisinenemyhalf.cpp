#include "layer/control/treenodedeciderisinenemyhalf.h"
#include "layer/control/treenoderesultdefendgoal.h"

using namespace RoboSoccer::Layer::Control;

TreeNodeDeciderIsInEnemyHalf::TreeNodeDeciderIsInEnemyHalf(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher) :
	TreeNodeDecider(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{
	m_childYes = new TreeNodeResultDefendGoal(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher);
	m_childNo = new TreeNodeResultDefendGoal(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher);

}

bool TreeNodeDeciderIsInEnemyHalf::calculateDecision()
{
	return false;
}
