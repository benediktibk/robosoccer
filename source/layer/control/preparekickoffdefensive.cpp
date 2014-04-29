#include "layer/control/preparekickoffdefensive.h"
#include "layer/control/kickoffdefensive.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

PrepareKickOffDefensive::PrepareKickOffDefensive(
		Logger &logger, RefereeBase &referee, Autonomous::Team &ownTeam,
		const Autonomous::EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, false),
	m_movementFinished(false)
{ }

State *PrepareKickOffDefensive::nextState()
{
	if (!m_referee.getPrepareForKickOff() && !m_referee.getExecuteKickOff())
		return new Pause(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball);
	else if (m_movementFinished && m_referee.getExecuteKickOff())
		return new KickOffDefensive(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball);

	return 0;
}

string PrepareKickOffDefensive::getName()
{
	return string("prepare kick off defensive");
}

void PrepareKickOffDefensive::updateInternal()
{
	//! @todo start and movement and wait for it
	m_movementFinished = true;
	m_referee.setReady();
}