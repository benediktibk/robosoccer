#include "layer/control/preparepenalty.h"
#include "layer/control/preparepenaltyoffensive.h"
#include "layer/control/preparepenaltydefensive.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PreparePenalty::PreparePenalty(Logger &logger, RefereeBase &referee, Autonomous::Team &ownTeam,
		const Autonomous::EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, false)
{ }

State *PreparePenalty::nextState()
{
	if (m_referee.hasKickOffOrPenalty())
		return new PreparePenaltyOffensive(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
	else
		return new PreparePenaltyDefensive(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
}

string PreparePenalty::getName()
{
	return string("prepare penalty");
}

void PreparePenalty::updateInternal()
{ }