#include "layer/control/treenodedeciderisonerobotbehindtheball.h"
#include "layer/control/treenoderesultgetbehindball.h"
#include "layer/control/treenoderesultfollowball.h"
#include "layer/abstraction/refereebase.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/robot.h"
#include "common/geometry/pose.h"
#include "common/other/compare.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;

TreeNodeDeciderIsOneRobotBehindTheBall::TreeNodeDeciderIsOneRobotBehindTheBall(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher) :
	TreeNodeDecider(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{
	m_childYes = new TreeNodeResultFollowBall(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
	m_childNo = new TreeNodeResultGetBehindBall(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
}

bool TreeNodeDeciderIsOneRobotBehindTheBall::calculateDecision()
{
	Pose robot1Pose = m_ownTeam.getFirstFieldPlayer().getCurrentPose();
	Pose robot2Pose = m_ownTeam.getSecondFieldPlayer().getCurrentPose();
	Point ballPosition = m_ball.getPosition();

	Point nearBall = ballPosition + Point(0, 0.3);
	Point farFromBall = ballPosition + Point(0,-0.3);

	if (m_referee.getOwnFieldSide() == FieldSideRight)
	{
		nearBall = nearBall +  Point(0,0);
		farFromBall = farFromBall + Point(3,0);
	}
	else
	{
		nearBall = nearBall + Point(0,0);
		farFromBall = farFromBall + Point(-3,0);
	}

	Rectangle behindBallZone(nearBall, farFromBall);
	Compare compare(0.01);

	return behindBallZone.isInside(robot1Pose.getPosition(), compare)
			|| behindBallZone.isInside(robot2Pose.getPosition(), compare);
}
