#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TEAM_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TEAM_H

#include "layer/autonomous/robot.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class Storage;
}
namespace Autonomous
{
	class IntelligentBall;

	class Team
	{
	public:
		Team(Abstraction::Storage &storage);

		Robot& getGoalie() const;
		Robot& getPlayerCloseToBall(const IntelligentBall &ball) const;

	private:
		Robot *m_goalie;
		Robot *m_player1;
		Robot *m_player2;
	};
}
}
}

#endif // ROBOSOCCER_LAYER_AUTONOMOUS_TEAM_H


