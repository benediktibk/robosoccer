#include "layer/control/penaltyoffensive.h"
#include "layer/control/play.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereebase.h"
#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "common/geometry/pose.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Control;

PenaltyOffensive::PenaltyOffensive(Logger &logger, RefereeBase &referee, Team &ownTeam,
		const EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball,
		Autonomous::TargetPositionFetcher const &targetPositionFetcher) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, false),
	m_calledGoTo(false),
	m_ballKicked(false)
{ }

State *PenaltyOffensive::nextState()
{
	if (m_referee.getContinuePlaying())
		return new Play(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
	else if (!m_referee.getExecutePenalty())
		return new Pause(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);

	return 0;
}

string PenaltyOffensive::getName()
{
	return string("penalty offensive");
}

void PenaltyOffensive::updateInternal()
{
	Robot &robot = m_ownTeam.getGoalie();

	if(!m_calledGoTo)
	{
		//! @todo consider ignoreBall and driveSlowlyAtTheEnd
		robot.goTo(m_targetPositionFetcher.getPenaltyPositionKicker(m_ball), DriveModeDefault);
		m_calledGoTo = true;
	}

	if(movementsFinished() && !m_ballKicked)
	{
		robot.kick(m_ball);
		m_ballKicked = true;
	}
}
