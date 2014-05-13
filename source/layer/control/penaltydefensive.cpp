#include "layer/control/penaltydefensive.h"
#include "layer/control/play.h"
#include "layer/control/pause.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/abstraction/refereebase.h"
#include "common/geometry/pose.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Autonomous;

PenaltyDefensive::PenaltyDefensive(Logger &logger, RefereeBase &referee, Autonomous::Team &ownTeam,
		const Autonomous::EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, false)
{ }

State *PenaltyDefensive::nextState()
{
	if (m_referee.getContinuePlaying())
		return new Play(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
	else if (!m_referee.getExecutePenalty())
		return new Pause(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);

	return 0;
}

string PenaltyDefensive::getName()
{
	return string("penalty defensive");
}

void PenaltyDefensive::updateInternal()
{
	Robot &goalie = m_ownTeam.getGoalie();
	goalie.goToDirect(m_targetPositionFetcher.getPenaltyPositionGoalie(m_ball));
}
