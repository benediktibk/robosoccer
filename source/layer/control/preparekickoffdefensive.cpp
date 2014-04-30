#include "layer/control/preparekickoffdefensive.h"
#include "layer/control/kickoffdefensive.h"
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

PrepareKickOffDefensive::PrepareKickOffDefensive(
		Logger &logger, RefereeBase &referee, Autonomous::TeamImpl &ownTeam,
		const Autonomous::EnemyTeamImpl &enemyTeam, const Autonomous::IntelligentBall &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher) :
	RoboSoccerState(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher, false),
	m_movementFinished(false)
{ }

State *PrepareKickOffDefensive::nextState()
{
	if (!m_referee.getPrepareForKickOff() && !m_referee.getExecuteKickOff())
		return new Pause(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);
	else if (m_movementFinished && m_referee.getExecuteKickOff())
		return new KickOffDefensive(m_logger, m_referee, m_ownTeam, m_enemyTeam, m_ball, m_targetPositionFetcher);

	return 0;
}

string PrepareKickOffDefensive::getName()
{
	return string("prepare kick off defensive");
}

void PrepareKickOffDefensive::updateInternal()
{
	Robot &goalie = m_ownTeam.getGoalie();
	Robot &fieldPlayerOne = m_ownTeam.getFirstFieldPlayer();
	Robot &fieldPlayerTwo = m_ownTeam.getSecondFieldPlayer();

	goalie.goTo(m_targetPositionFetcher.getStartPositionGoalkeeper());
	fieldPlayerOne.goTo(m_targetPositionFetcher.getStartPositionPlayerOneDefensive());
	fieldPlayerTwo.goTo(m_targetPositionFetcher.getStartPositionPlayerTwoDefensive());

	//! @todo wait till the movement is finished
	m_movementFinished = true;
	m_referee.setReady();
}