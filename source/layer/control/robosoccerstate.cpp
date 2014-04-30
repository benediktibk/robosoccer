#include "layer/control/robosoccerstate.h"

using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Logging;

RoboSoccerState::RoboSoccerState(Logger &logger, RefereeBase &referee, Team &ownTeam,
		EnemyTeam const &enemyTeam, IntelligentBall const &ball, const TargetPositionFetcher &targetPositionFetcher,
		bool callUpdateOnlyOnce) :
	Common::States::State(logger, callUpdateOnlyOnce),
	m_referee(referee),
	m_ownTeam(ownTeam),
	m_enemyTeam(enemyTeam),
	m_ball(ball),
	m_targetPositionFetcher(targetPositionFetcher)
{ }