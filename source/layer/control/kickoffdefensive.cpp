#include "layer/control/kickoffdefensive.h"
#include "layer/control/play.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;

KickOffDefensive::KickOffDefensive(Logger &logger, RefereeBase &referee, Autonomous::Team &ownTeam, const Autonomous::EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, false)
{ }

State *KickOffDefensive::nextState()
{
	if (m_referee.getContinuePlaying())
		return new Play(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball);
	else if (!m_referee.getExecuteKickOff())
		return new Pause(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball);

	return 0;
}

string KickOffDefensive::getName()
{
	return string("kick off defensive");
}

void KickOffDefensive::updateInternal()
{

}