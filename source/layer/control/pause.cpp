#include "layer/control/pause.h"
#include "layer/control/preparekickoff.h"
#include "layer/control/preparepenalty.h"
#include "layer/control/play.h"
#include "layer/control/userinputfetcherimpl.h"
#include "layer/autonomous/teamimpl.h"
#include "layer/autonomous/robot.h"
#include "layer/abstraction/refereebase.h"

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

Pause::Pause(Logger &logger, RefereeBase &referee,
			 Team &ownTeam, const EnemyTeam &enemyTeam,
			 Autonomous::IntelligentBall const &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher,
			 FieldPositionCheckerGoalkeeper const &fieldPositionCheckerGoalKeeper) :
	RoboSoccerState(
		logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher,
		fieldPositionCheckerGoalKeeper, true)
{ }

State* Pause::nextState()
{
	if (m_referee.getPrepareForKickOff())
		return new PrepareKickOff(
					m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball,
					m_targetPositionFetcher, m_fieldPositionCheckerGoalKeeper);
	else if (m_referee.getPrepareForPenalty())
		return new PreparePenalty(
					m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball,
					m_targetPositionFetcher, m_fieldPositionCheckerGoalKeeper, new UserInputFetcherImpl());
	else if (m_referee.getContinuePlaying())
		return new Play(
					m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball,
					m_targetPositionFetcher, m_fieldPositionCheckerGoalKeeper);

	return 0;
}

string Pause::getName()
{
	return string("pause");
}

void Pause::updateInternal()
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		Robot &robot = m_ownTeam.getRobotByNumber(i);
		robot.stop();
	}
}
