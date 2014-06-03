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

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;

TreeNodeDeciderIsOneRobotInShootingRange::TreeNodeDeciderIsOneRobotInShootingRange(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher) :
	TreeNodeDecider(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{ }

bool TreeNodeDeciderIsOneRobotInShootingRange::calculateDecision()
{
	Pose robot1Pose = m_ownTeam.getFirstFieldPlayer().getCurrentPose();
	Pose robot2Pose = m_ownTeam.getSecondFieldPlayer().getCurrentPose();
	Point ballPosition = m_ball.getPosition();

	//! @todo find shooting range
	if (ballPosition.distanceTo(robot1Pose.getPosition()) > 0.3
			&& ballPosition.distanceTo(robot2Pose.getPosition()) > 0.3)
		return false;

	Point yCoordinate;

	if (m_referee.getOwnFieldSide() == FieldSideRight)
		yCoordinate = Point(0.2,0);
	else
		yCoordinate = Point(-0.2,0);

	Point nearBall = ballPosition + Point(0,0.1);
	Point farFromBall = ballPosition + Point(0,-0.1) + yCoordinate;
	Rectangle shootingZone(nearBall, farFromBall);

	Compare compare(0.01);

	return shootingZone.isInside(robot1Pose.getPosition(), compare)
			|| shootingZone.isInside(robot2Pose.getPosition(), compare);
}
