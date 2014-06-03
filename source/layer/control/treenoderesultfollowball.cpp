#include "layer/control/treenoderesultfollowball.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Control;


TreeNodeResultFollowBall::TreeNodeResultFollowBall(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher) :
	TreeNodeResult(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{

}

void TreeNodeResultFollowBall::execute()
{
	Robot &robot1 = m_ownTeam.getFirstFieldPlayer();
	Robot &robot2 = m_ownTeam.getSecondFieldPlayer();

	Pose target(m_ball.getPosition(), Angle());
	Pose alternativeTarget = Pose(m_targetPositionFetcher.getAlternativeRobotPositionAtBallHeightAggressiveMode(m_ball, target.getPosition()).front(), Angle());

	if (robot1.getCurrentPose().distanceTo(target) <
			robot2.getCurrentPose().distanceTo(target))
	{
		robot1.goTo(target, true, true, false);
		robot2.goTo(alternativeTarget, false, false, false);
	}
	else
	{
		robot2.goTo(target, true, true, false);
		robot1.goTo(alternativeTarget, false, false, false);
	}
}
