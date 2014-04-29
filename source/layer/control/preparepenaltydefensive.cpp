#include "layer/control/preparepenaltydefensive.h"
#include "layer/control/penaltydefensive.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PreparePenaltyDefensive::PreparePenaltyDefensive(
		Logger &logger, RefereeBase &referee, Autonomous::Team &ownTeam,
		const Autonomous::EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, false),
	m_movementFinished(false)
{ }

State *PreparePenaltyDefensive::nextState()
{
	if (!m_referee.getPrepareForPenalty() && !m_referee.getExecutePenalty())
		return new Pause(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball);
	else if (m_movementFinished && m_referee.getExecutePenalty())
		return new PenaltyDefensive(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball);

	return 0;
}

string PreparePenaltyDefensive::getName()
{
	return string("prepare penalty defensive");
}

void PreparePenaltyDefensive::updateInternal()
{
	//! @todo start and movement and wait for it
	m_movementFinished = true;
	m_referee.setReady();
}