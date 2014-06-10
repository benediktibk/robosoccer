#include "layer/control/treenoderesultshoot.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "common/geometry/pose.h"
#include "common/other/compare.h"
#include <iostream>

using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Control;


TreeNodeResultShoot::TreeNodeResultShoot(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher) :
	TreeNodeResult(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{

}

void TreeNodeResultShoot::execute()
{
	Robot &robotCloseToBall = m_ownTeam.getPlayerCloserToBall(m_ball);
	Robot &robotFarFromBall = m_ownTeam.getPlayerFartherAwayFromBall(m_ball);

	if (m_targetPositionFetcher.isGoodKickPosition(m_ball, robotCloseToBall.getCurrentPose().getPosition(), 0.3))
	{
		robotCloseToBall.kick(m_ball);
		return;
	}

	if (m_targetPositionFetcher.isGoodKickPosition(m_ball, robotFarFromBall.getCurrentPose().getPosition(), 0.3))
	{
		robotFarFromBall.kick(m_ball);
		return;
	}
}
