#include "layer/control/preparepenaltydefensive.h"
#include "layer/control/penaltydefensive.h"
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

PreparePenaltyDefensive::PreparePenaltyDefensive(Logger &logger, RefereeBase &referee, Team &ownTeam,
		const EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, false),
	m_movementFinished(false),
	m_sendGoToSignal(false)
{ }

State *PreparePenaltyDefensive::nextState()
{
	if (!m_referee.getPrepareForPenalty() && !m_referee.getExecutePenalty())
		return new Pause(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
	else if (m_movementFinished && m_referee.getExecutePenalty())
		return new PenaltyDefensive(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);

	return 0;
}

string PreparePenaltyDefensive::getName()
{
	return string("prepare penalty defensive");
}

void PreparePenaltyDefensive::updateInternal()
{
	if (m_movementFinished)
		return;

	Robot &goalie = m_ownTeam.getGoalie();
	Robot &fieldPlayerOne = m_ownTeam.getFirstFieldPlayer();
	Robot &fieldPlayerTwo = m_ownTeam.getSecondFieldPlayer();

	//! @todo consider ignoreBall and driveSlowlyAtTheEnd
	if (!m_sendGoToSignal)
	{
		m_sendGoToSignal = true;
		goalie.goTo(m_targetPositionFetcher.getPenaltyPositionGoalie(m_ball), DriveModeIgnoreGoalObstacles);
		fieldPlayerOne.goTo(m_targetPositionFetcher.getPenaltyPositionsUnusedPlayerOne(), DriveModeDriveSlowlyAtTheEnd);
		fieldPlayerTwo.goTo(m_targetPositionFetcher.getPenaltyPositionsUnusedPlayerTwo(), DriveModeDriveSlowlyAtTheEnd);
	}
	if (movementsFinished())
	{
		m_movementFinished = true;
		m_referee.setReady();
	}
}
