#include "layer/control/treenoderesultgetbehindball.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/robot.h"
#include "common/geometry/pose.h"
#include "common/other/signum.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;
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

	Pose targetShort = m_targetPositionFetcher.getTargetBehindBall(m_ball, 0.3);
	Pose targetLong = m_targetPositionFetcher.getTargetBehindBall(m_ball, 0.6);

	Point targetShortPosition = targetShort.getPosition();
	if (fabs(targetShortPosition.getX()) > 1.45)
	{
		//! We should consider to ignore the ball in this case
		targetShortPosition.setX(sgn(targetShortPosition.getX()) * 1.45);

		//! @todo use a useful position for second player
	}

	if (robot1.getCurrentPose().distanceTo(targetShort) <
			robot2.getCurrentPose().distanceTo(targetShort))
	{
		robot1.goTo(targetShort, false, false, false);
		robot2.goTo(targetLong, false, false, false);
	}
	else
	{
		robot2.goTo(targetShort, false, false, false);
		robot1.goTo(targetLong, false, false, false);
	}

}
