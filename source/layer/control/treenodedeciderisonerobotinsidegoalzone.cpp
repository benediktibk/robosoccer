#include "layer/control/treenodedeciderisonerobotinsidegoalzone.h"
#include "layer/control/treenodedeciderisonerobotinshootingrange.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/robot.h"
#include "layer/abstraction/fieldpositioncheckerfieldplayer.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;

TreeNodeDeciderIsOneRobotInsideGoalZone::TreeNodeDeciderIsOneRobotInsideGoalZone(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher) :
	TreeNodeDecider(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{
	//! @todo use useful YES TreeNode
	m_childYes = new TreeNodeDeciderIsOneRobotInShootingRange(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
	m_childNo = new TreeNodeDeciderIsOneRobotInShootingRange(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
}

bool TreeNodeDeciderIsOneRobotInsideGoalZone::calculateDecision()
{
	Pose robot1Pose = m_ownTeam.getFirstFieldPlayer().getCurrentPose();
	Pose robot2Pose = m_ownTeam.getSecondFieldPlayer().getCurrentPose();
	FieldPositionCheckerFieldPlayer fieldPositionChecker;

	return fieldPositionChecker.isPointInsideGoalZone(robot1Pose)
			|| fieldPositionChecker.isPointInsideGoalZone(robot2Pose);
}
