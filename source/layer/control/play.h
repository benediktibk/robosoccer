#ifndef ROBOSOCCER_LAYER_CONTROL_PLAY_H
#define ROBOSOCCER_LAYER_CONTROL_PLAY_H

#include "layer/control/robosoccerstate.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class Play : public RoboSoccerState
	{
	public:
		Play(Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
			 Autonomous::TeamImpl &ownTeam, Autonomous::EnemyTeamImpl const &enemyTeam,
			 Autonomous::IntelligentBall const &ball, Autonomous::TargetPositionFetcher const &targetPositionFetcher);

		virtual Common::States::State* nextState();
		virtual std::string getName();

	private:
		virtual void updateInternal();
	};
}
}
}

#endif


