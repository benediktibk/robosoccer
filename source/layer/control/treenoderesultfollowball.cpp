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
	Robot &robotOne = m_ownTeam.getFirstFieldPlayer();
	Robot &robotTwo = m_ownTeam.getSecondFieldPlayer();

	if (m_targetPositionFetcher.isPositionBehindTheBall(robotOne.getCurrentPose(), m_ball))
	{
		vector<Pose> targetsOnBall = m_targetPositionFetcher.getPositionsToDriveOnBall(m_ball);
		vector<Pose> targetsAlternativePlayer = m_targetPositionFetcher.getAlternativeRobotPositionsBehindBallAggressiveMode(m_ball);

		robotOne.goTo(targetsOnBall, DriveModeIgnoreBall);
		robotTwo.goTo(targetsAlternativePlayer, DriveModeDefault);
	}
	else
	{
		vector<Pose> targetsOnBall = m_targetPositionFetcher.getPositionsToDriveOnBall(m_ball);
		vector<Pose> targetsAlternativePlayer = m_targetPositionFetcher.getAlternativeRobotPositionsBehindBallAggressiveMode(m_ball);

		robotTwo.goTo(targetsOnBall, DriveModeIgnoreBall);
		robotOne.goTo(targetsAlternativePlayer, DriveModeDefault);
	}
}
