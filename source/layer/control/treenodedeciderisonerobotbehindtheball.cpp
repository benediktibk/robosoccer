#include "layer/control/treenodedeciderisonerobotbehindtheball.h"
#include "layer/control/treenoderesultgetbehindball.h"
#include "layer/control/treenoderesultfollowball.h"
#include "layer/abstraction/refereebase.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/robot.h"
#include "common/geometry/pose.h"
#include "common/geometry/angle.h"
#include "common/geometry/straight.h"
#include "common/other/compare.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;

TreeNodeDeciderIsOneRobotBehindTheBall::TreeNodeDeciderIsOneRobotBehindTheBall(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher,
		FollowBallRobot lastFollowBallRobot) :
	TreeNodeDecider(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, lastFollowBallRobot)
{
	m_childYes = new TreeNodeResultFollowBall(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher, m_lastFollowBallRobot);
	m_childNo = new TreeNodeResultGetBehindBall(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher, m_lastFollowBallRobot);
}

bool TreeNodeDeciderIsOneRobotBehindTheBall::calculateDecision()
{
	Pose robot1Pose = m_ownTeam.getFirstFieldPlayer().getCurrentPose();
	Pose robot2Pose = m_ownTeam.getSecondFieldPlayer().getCurrentPose();

	return m_targetPositionFetcher.isPositionBehindTheBall(robot1Pose, m_ball)
			|| m_targetPositionFetcher.isPositionBehindTheBall(robot2Pose, m_ball);
}
