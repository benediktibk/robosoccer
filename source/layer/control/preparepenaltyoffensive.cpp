#include "layer/control/preparepenaltyoffensive.h"
#include "layer/control/penaltyoffensive.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereebase.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "common/geometry/pose.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PreparePenaltyOffensive::PreparePenaltyOffensive(Logger &logger, RefereeBase &referee, Autonomous::Team &ownTeam,
		const Autonomous::EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, false),
	m_movementFinished(false)
{ }

State *PreparePenaltyOffensive::nextState()
{
	if (!m_referee.getPrepareForPenalty() && !m_referee.getExecutePenalty())
		return new Pause(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
	else if (m_movementFinished && m_referee.getExecutePenalty())
		return new PenaltyOffensive(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);

	return 0;
}

string PreparePenaltyOffensive::getName()
{
	return string("prepare penalty offensive");
}

void PreparePenaltyOffensive::updateInternal()
{
	if (m_movementFinished)
		return;

	Robot &playerOne = m_ownTeam.getFirstFieldPlayer();
	Robot &playerTwo = m_ownTeam.getSecondFieldPlayer();
	Robot &goalie = m_ownTeam.getGoalie();

	//! @todo consider ignoreBall and driveSlolyAtTheEnd
	playerOne.goTo(m_targetPositionFetcher.getPenaltyPositionsUnusedPlayerOne(), DriveModeDefault);
	playerTwo.goTo(m_targetPositionFetcher.getPenaltyPositionsUnusedPlayerTwo(), DriveModeDefault);
	goalie.goTo(m_targetPositionFetcher.getPenaltyPositionsPrepareKicker(), DriveModeIgnoreGoalObstacles);

	if (movementsFinished())
	{
		m_movementFinished = true;
		m_referee.setReady();
	}
}
