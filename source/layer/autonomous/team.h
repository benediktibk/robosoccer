#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TEAM_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TEAM_H

#include "layer/autonomous/robot.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class IntelligentBall;

	class Team
	{
	public:
		Team(Robot &goalie, Robot &player1, Robot &player2);

		Robot& getGoalie() const;
		Robot& getPlayerCloseToBall(const IntelligentBall &ball) const;

	private:
		Robot &m_goalie;
		Robot &m_player1;
		Robot &m_player2;
	};
}
}
}

#endif // ROBOSOCCER_LAYER_AUTONOMOUS_TEAM_H


