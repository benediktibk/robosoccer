#include "layer/control/treenoderesultfollowball.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "common/geometry/pose.h"
#include <iostream>
#include <assert.h>

using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Control;
using namespace std;

TreeNodeResultFollowBall::TreeNodeResultFollowBall(Common::Logging::Logger &logger, RefereeBase &referee, Team &ownTeam, const EnemyTeam &enemyTeam,
		const IntelligentBall &ball, const TargetPositionFetcher &targetPositionFetcher, FollowBallRobot lastFollowBallRobot) :
	TreeNodeResult(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, lastFollowBallRobot)
{ }

void TreeNodeResultFollowBall::execute()
{
	Robot &robotOne = m_ownTeam.getFirstFieldPlayer();
	Robot &robotTwo = m_ownTeam.getSecondFieldPlayer();
	Point ballPosition = m_ball.getPosition();

	if (m_lastFollowBallRobot == FollowBallRobotNone)
	{

		double distanceRobotOneToBall = ballPosition.distanceTo(robotOne.getCurrentPose());
		double distanceRobotTwoToBall = ballPosition.distanceTo(robotTwo.getCurrentPose());

		if (m_targetPositionFetcher.isPositionBehindTheBall(robotOne.getCurrentPose(), m_ball)
				&& (!(m_targetPositionFetcher.isPositionBehindTheBall(robotTwo.getCurrentPose(), m_ball)) || distanceRobotOneToBall < distanceRobotTwoToBall))
		{
			m_lastFollowBallRobot = FollowBallRobotOne;
		}
		else
		{
			m_lastFollowBallRobot = FollowBallRobotTwo;
		}
	}

	if (m_lastFollowBallRobot == FollowBallRobotOne)
	{
		DriveMode driveMode = DriveModeIgnoreBall;
		if (!m_targetPositionFetcher.isPositionBehindTheBallWithAngle(robotOne.getCurrentPose(), m_ball, Angle::getHalfRotation()))
			driveMode = DriveModeDefault;

		vector<Pose> targetsOnBall = m_targetPositionFetcher.getPositionsToDriveOnBall(m_ball);
		vector<Pose> targetsAlternativePlayer = m_targetPositionFetcher.getAlternativeRobotPositionsBehindBallAggressiveMode(m_ball);

		robotOne.goTo(targetsOnBall, driveMode);
		robotTwo.goTo(targetsAlternativePlayer, DriveModeDefault);
	}
	else if (m_lastFollowBallRobot == FollowBallRobotTwo)
	{
		DriveMode driveMode = DriveModeIgnoreBall;
		if (!m_targetPositionFetcher.isPositionBehindTheBallWithAngle(robotTwo.getCurrentPose(), m_ball, Angle::getHalfRotation()))
			driveMode = DriveModeDefault;

		vector<Pose> targetsOnBall = m_targetPositionFetcher.getPositionsToDriveOnBall(m_ball);
		vector<Pose> targetsAlternativePlayer = m_targetPositionFetcher.getAlternativeRobotPositionsBehindBallAggressiveMode(m_ball);

		robotTwo.goTo(targetsOnBall, driveMode);
		robotOne.goTo(targetsAlternativePlayer, DriveModeDefault);
	}
	else
		assert(false);

}
