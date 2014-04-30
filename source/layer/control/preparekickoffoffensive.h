#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFOFFENSIVE_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFOFFENSIVE_H

#include "layer/control/robosoccerstate.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PrepareKickOffOffensive :
			public RoboSoccerState
	{
	public:
		PrepareKickOffOffensive(Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
								Autonomous::TeamImpl &ownTeam, Autonomous::EnemyTeamImpl const &enemyTeam,
								Autonomous::IntelligentBall const &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher);

		virtual Common::States::State* nextState();
		virtual std::string getName();

	private:
		virtual void updateInternal();

	private:
		bool m_movementFinished;
	};
}
}
}

#endif


