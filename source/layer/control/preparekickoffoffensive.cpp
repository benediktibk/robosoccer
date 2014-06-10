#include "layer/control/preparekickoffoffensive.h"
#include "layer/control/kickoffoffensive.h"
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

PrepareKickOffOffensive::PrepareKickOffOffensive(Logger &logger, RefereeBase &referee, Team &ownTeam,
		const EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, false),
	m_movementFinished(false)
{ }

State *PrepareKickOffOffensive::nextState()
{
	if (!m_referee.getPrepareForKickOff() && !m_referee.getExecuteKickOff())
		return new Pause(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
	else if (m_movementFinished && m_referee.getExecuteKickOff())
		return new KickOffOffensive(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);

	return 0;
}

string PrepareKickOffOffensive::getName()
{
	return string("prepare kick off offensive");
}

void PrepareKickOffOffensive::updateInternal()
{
	if (m_movementFinished)
		return;

	Robot &goalie = m_ownTeam.getGoalie();
	Robot &fieldPlayerOne = m_ownTeam.getFirstFieldPlayer();
	Robot &fieldPlayerTwo = m_ownTeam.getSecondFieldPlayer();

	//! @todo consider ignoreBall and driveSlolyAtTheEnd
	goalie.goTo(m_targetPositionFetcher.getStartPositionsGoalkeeper(), DriveModeIgnoreGoalObstacles);
	fieldPlayerOne.goTo(m_targetPositionFetcher.getStartPositionsPlayerOneOffensive(), DriveModeDefault);
	fieldPlayerTwo.goTo(m_targetPositionFetcher.getStartPositionsPlayerTwoOffensive(), DriveModeDefault);

	if (movementsFinished())
	{
		m_movementFinished = true;
		m_referee.setReady();
	}
}
