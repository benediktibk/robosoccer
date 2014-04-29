#ifndef ROBOSOCCER_LAYER_CONTROL_ROBOSOCCERSTATE_H
#define ROBOSOCCER_LAYER_CONTROL_ROBOSOCCERSTATE_H

#include "common/states/state.h"

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
	class Logger;
}
}
namespace Layer
{
namespace Abstraction
{
	class RefereeBase;
}
namespace Autonomous
{
	class EnemyTeam;
	class Team;
	class IntelligentBall;
}
namespace Control
{
	class RoboSoccerState : public Common::States::State
	{
	public:
		RoboSoccerState(
				Common::Logging::Logger &logger, Abstraction::RefereeBase &referee,
				Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
				Autonomous::IntelligentBall const &ball, bool callUpdateOnlyOnce);

	protected:
		Abstraction::RefereeBase &m_referee;
		Autonomous::Team &m_ownTeam;
		const Autonomous::EnemyTeam &m_enemyTeam;
		const Autonomous::IntelligentBall &m_ball;

	};
}
}
}

#endif

