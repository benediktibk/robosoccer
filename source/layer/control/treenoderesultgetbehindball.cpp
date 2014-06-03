#include "layer/control/treenoderesultgetbehindball.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/robot.h"
#include "common/geometry/pose.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Control;

TreeNodeResultGetBehindBall::TreeNodeResultGetBehindBall(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher) :
	TreeNodeResult(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{

}

void TreeNodeResultGetBehindBall::execute()
{
	//! @todo use useful target for second robot
	Robot &robot1 = m_ownTeam.getFirstFieldPlayer();
	Robot &robot2 = m_ownTeam.getSecondFieldPlayer();

	Point target;
	if (m_ball.isMoving())
		target = m_targetPositionFetcher.getPointBehindBallInMovingDirection(m_ball, 0.3);

	else
		target = m_targetPositionFetcher.getPointBehindBallInMovingDirection(m_ball, 0.1);

	if (robot1.getCurrentPose().getPosition().distanceTo(target) <
			robot2.getCurrentPose().getPosition().distanceTo(target))
	{
		robot1.goTo(Pose(target, Angle()), false, false, false);
	}

}
