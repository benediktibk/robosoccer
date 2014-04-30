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

PreparePenaltyDefensive::PreparePenaltyDefensive(
		Logger &logger, RefereeBase &referee, Autonomous::TeamImpl &ownTeam,
		const Autonomous::EnemyTeamImpl &enemyTeam, const Autonomous::IntelligentBall &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, false),
	m_movementFinished(false)
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
	//! @todo move goalie to a better position

	//! @todo wait till the movement is finished
	m_movementFinished = true;
	m_referee.setReady();
}