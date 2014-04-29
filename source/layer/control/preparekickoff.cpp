#include "layer/control/preparekickoff.h"
#include "layer/control/preparekickoffoffensive.h"
#include "layer/control/preparekickoffdefensive.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PrepareKickOff::PrepareKickOff(
		Logger &logger, RefereeBase &referee, Autonomous::Team &ownTeam,
		const Autonomous::EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, false)
{ }

State *PrepareKickOff::nextState()
{
	if (m_referee.hasKickOffOrPenalty())
		return new PrepareKickOffOffensive(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball);
	else
		return new PrepareKickOffDefensive(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball);
}

string PrepareKickOff::getName()
{
	return string("prepare kick off");
}

void PrepareKickOff::updateInternal()
{ }