#include "layer/control/treenodedeciderisonerobotinshootingrange.h"
#include "layer/control/treenoderesultgetbehindball.h"
#include "layer/control/treenoderesultshoot.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/robot.h"
#include "layer/abstraction/refereebase.h"
#include "common/geometry/pose.h"
#include "common/geometry/rectangle.h"
#include "common/other/compare.h"
#include "layer/control/treenoderesultshoot.h"
#include "layer/control/treenodedeciderisonerobotbehindtheball.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;

TreeNodeDeciderIsOneRobotInShootingRange::TreeNodeDeciderIsOneRobotInShootingRange(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher) :
	TreeNodeDecider(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{
	m_childYes = new TreeNodeResultShoot(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
	m_childNo = new TreeNodeDeciderIsOneRobotBehindTheBall(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
}

bool TreeNodeDeciderIsOneRobotInShootingRange::calculateDecision()
{
	Pose robot1Pose = m_ownTeam.getFirstFieldPlayer().getCurrentPose();
	Pose robot2Pose = m_ownTeam.getSecondFieldPlayer().getCurrentPose();

	//! @todo find shooting range

	return m_targetPositionFetcher.isGoodKickPosition(m_ball, robot1Pose.getPosition(), 0.3)
			|| m_targetPositionFetcher.isGoodKickPosition(m_ball, robot2Pose.getPosition(), 0.3);
}
