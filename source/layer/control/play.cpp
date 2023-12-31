#include "layer/control/play.h"
#include "layer/control/pause.h"
#include "layer/control/treenodedeciderisonerobotinsidegoalzone.h"
#include "layer/control/treenoderesult.h"
#include "layer/abstraction/refereebase.h"
#include "layer/abstraction/fieldpositioncheckergoalkeeper.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "common/geometry/pose.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

Play::Play(Logger &logger, RefereeBase &referee, Autonomous::Team &ownTeam,
		const Autonomous::EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball,
		Autonomous::TargetPositionFetcher const &targetPositionFetcher, FieldPositionCheckerGoalkeeper &fieldPositionCheckerGoalKeeper) :
	RoboSoccerState(
		logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher,
		fieldPositionCheckerGoalKeeper, false),
	m_lastFollowBall(TreeNode::FollowBallRobotNone)
{ }

State *Play::nextState()
{
	if (!m_referee.getContinuePlaying())
		return new Pause(
					m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball,
					m_targetPositionFetcher, m_fieldPositionCheckerGoalKeeper);

	return 0;
}

string Play::getName()
{
	return string("play");
}

void Play::updateInternal()
{
	Pose goalKeeperTarget = m_targetPositionFetcher.getTargetForGoalkeeper(m_ball);
	Point ballPosition = m_ball.getPosition();
	Robot &goalie = m_ownTeam.getGoalie();

	if (m_fieldPositionCheckerGoalKeeper.isPointInsideDangerZone(ballPosition))
		goalie.stop();
	else if (m_fieldPositionCheckerGoalKeeper.isPointInsideGoalZone(goalie.getCurrentPose()))
		goalie.goToDirect(goalKeeperTarget);
	else
	{
		vector<Pose> targets;
		targets.push_back(goalKeeperTarget);
		goalie.goTo(targets, DriveModeIgnoreGoalObstacles);
	}

	TreeNode *node = new TreeNodeDeciderIsOneRobotInsideGoalZone(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher, m_lastFollowBall);
	while (node->decide())
	{
		TreeNodeDecider *current = dynamic_cast<TreeNodeDecider*>(node);
		node = current->getChild();
		delete current;
		current = 0;
	}

	TreeNodeResult *result = dynamic_cast<TreeNodeResult*>(node);
	result->execute();
	m_lastFollowBall = result->getLastFollowBallRobot();
	delete result;
	result = 0;
}
