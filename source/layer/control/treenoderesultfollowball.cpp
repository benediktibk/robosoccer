#include "layer/control/treenoderesultfollowball.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "common/geometry/pose.h"
#include <iostream>

using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Control;
using namespace std;

TreeNodeResultFollowBall::TreeNodeResultFollowBall(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher) :
	TreeNodeResult(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{ }

void TreeNodeResultFollowBall::execute()
{
	Robot &robotCloser = m_ownTeam.getPlayerCloserToBall(m_ball);
	Robot &robotFartherAway = m_ownTeam.getPlayerFartherAwayFromBall(m_ball);

	vector<Pose> targetsOnBall = m_targetPositionFetcher.getPositionsToDriveOnBall(m_ball);
	vector<Pose> targetsAlternativePlayer = m_targetPositionFetcher.getAlternativeRobotPositionsAtBallHeightAggressiveMode(m_ball, robotFartherAway.getCurrentPose().getPosition());
	robotCloser.goTo(targetsOnBall, DriveModeIgnoreBallAndDriveSlowlyAtTheEnd);
	robotFartherAway.goTo(targetsAlternativePlayer, DriveMoveDefault);
}
