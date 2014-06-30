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
using namespace std;

TreeNodeResultGetBehindBall::TreeNodeResultGetBehindBall(RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher, FollowBallRobot lastFollowBallRobot) :
	TreeNodeResult(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, lastFollowBallRobot)
{ }

void TreeNodeResultGetBehindBall::execute()
{
	Robot &robot1 = m_ownTeam.getFirstFieldPlayer();
	Robot &robot2 = m_ownTeam.getSecondFieldPlayer();

	vector<Pose> targetsBehindBall = m_targetPositionFetcher.getTargetsBehindBall(m_ball);
	vector<Pose> targetsBehindBallAlternativeRobot = m_targetPositionFetcher.getTargetsBehindBallAlternativeRobot(m_ball);
	DriveMode driveMode = DriveModeDefault;

	if (robot1.getCurrentPose().distanceTo(targetsBehindBall.front()) <
			robot2.getCurrentPose().distanceTo(targetsBehindBall.front()))
	{
		robot1.goTo(targetsBehindBall, driveMode);
		robot2.goTo(targetsBehindBallAlternativeRobot, DriveModeDefault);
	}
	else
	{
		robot2.goTo(targetsBehindBall, driveMode);
		robot1.goTo(targetsBehindBallAlternativeRobot, DriveModeDefault);
	}

}
