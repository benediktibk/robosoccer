#include "layer/control/treenoderesultleavegoalzone.h"
#include "layer/abstraction/fieldpositioncheckerfieldplayer.h"
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

TreeNodeResultLeaveGoalZone::TreeNodeResultLeaveGoalZone(RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher, FollowBallRobot lastFollowBallRobot) :
	TreeNodeResult(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, lastFollowBallRobot)
{ }

void TreeNodeResultLeaveGoalZone::execute()
{
	m_lastFollowBallRobot = FollowBallRobotNone;

	Pose robot1Pose = m_ownTeam.getFirstFieldPlayer().getCurrentPose();
	Pose robot2Pose = m_ownTeam.getSecondFieldPlayer().getCurrentPose();
	FieldPositionCheckerFieldPlayer fieldPositionChecker;

	if (fieldPositionChecker.isPointInsideGoalZone(robot1Pose))
		m_ownTeam.getFirstFieldPlayer().goTo(m_targetPositionFetcher.getPositionsToGetOutOfGoalZone(robot1Pose), DriveModeDefault);

	if (fieldPositionChecker.isPointInsideGoalZone(robot2Pose))
		m_ownTeam.getSecondFieldPlayer().goTo(m_targetPositionFetcher.getPositionsToGetOutOfGoalZone(robot2Pose), DriveModeDefault);

}
