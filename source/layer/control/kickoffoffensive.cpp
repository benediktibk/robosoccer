#include "layer/control/kickoffoffensive.h"
#include "layer/control/play.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;

KickOffOffensive::KickOffOffensive(Logger &logger, RefereeBase &referee, Autonomous::Team &ownTeam, const Autonomous::EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, false)
{ }

State *KickOffOffensive::nextState()
{
	if (m_referee.getContinuePlaying())
		return new Play(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
	else if (!m_referee.getExecuteKickOff())
		return new Pause(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);

	return 0;
}

string KickOffOffensive::getName()
{
	return string("kick off offensive");
}

void KickOffOffensive::updateInternal()
{

}