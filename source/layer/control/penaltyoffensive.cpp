#include "layer/control/penaltyoffensive.h"
#include "layer/control/play.h"
#include "layer/control/pause.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Control;

PenaltyOffensive::PenaltyOffensive(
		Logger &logger, RefereeBase &referee, Autonomous::Team &ownTeam,
		const Autonomous::EnemyTeam &enemyTeam, const Autonomous::IntelligentBall &ball) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, false)
{ }

State *PenaltyOffensive::nextState()
{
	if (m_referee.getContinuePlaying())
		return new Play(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball);
	else if (!m_referee.getExecutePenalty())
		return new Pause(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball);

	return 0;
}

string PenaltyOffensive::getName()
{
	return string("penalty offensive");
}

void PenaltyOffensive::updateInternal()
{

}