#include "layer/control/preparekickoffdefensive.h"
#include "layer/control/kickoffdefensive.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereebase.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "common/geometry/pose.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PrepareKickOffDefensive::PrepareKickOffDefensive(Logger &logger, RefereeBase &referee, Team &ownTeam,
		const EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball,
		Autonomous::TargetPositionFetcher const &targetPositionFetcher,
		FieldPositionCheckerGoalkeeper &fieldPositionCheckerGoalKeeper) :
	RoboSoccerState(
		logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher,
		fieldPositionCheckerGoalKeeper, false),
	m_movementFinished(false)
{ }

State *PrepareKickOffDefensive::nextState()
{
	if (!m_referee.getPrepareForKickOff() && !m_referee.getExecuteKickOff())
		return new Pause(
					m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball,
					m_targetPositionFetcher, m_fieldPositionCheckerGoalKeeper);
	else if (m_movementFinished && m_referee.getExecuteKickOff())
		return new KickOffDefensive(
					m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball,
					m_targetPositionFetcher, m_fieldPositionCheckerGoalKeeper);

	return 0;
}

string PrepareKickOffDefensive::getName()
{
	return string("prepare kick off defensive");
}

void PrepareKickOffDefensive::updateInternal()
{
	if (m_movementFinished)
		return;

	Robot &goalie = m_ownTeam.getGoalie();
	Robot &fieldPlayerOne = m_ownTeam.getFirstFieldPlayer();
	Robot &fieldPlayerTwo = m_ownTeam.getSecondFieldPlayer();

	goalie.goTo(m_targetPositionFetcher.getStartPositionsGoalkeeper(), DriveModeIgnoreGoalObstacles);
	fieldPlayerOne.goTo(m_targetPositionFetcher.getStartPositionsPlayerOneDefensive(), DriveModeDriveSlowlyAtTheEnd);
	fieldPlayerTwo.goTo(m_targetPositionFetcher.getStartPositionsPlayerTwoDefensive(), DriveModeDriveSlowlyAtTheEnd);

	if (movementsFinished())
	{
		m_movementFinished = true;
		m_referee.setReady();
	}
}
