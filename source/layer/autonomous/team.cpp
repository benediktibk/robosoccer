#include "layer/autonomous/team.h"
#include "layer/autonomous/intelligentball.h"

using namespace RoboSoccer::Layer::Autonomous;

Team::Team(Robot &goalie, Robot &player1, Robot &player2) :
	m_goalie(goalie),
	m_player1(player1),
	m_player2(player2)
{ }

Robot& Team::getGoalie() const
{
	return m_goalie;
}

Robot& Team::getPlayerCloseToBall(const IntelligentBall &/*ball*/) const
{
	return m_player1;
}

