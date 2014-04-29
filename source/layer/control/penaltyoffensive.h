#ifndef ROBOSOCCER_LAYER_CONTROL_PENALTYOFFENSIVE_H
#define ROBOSOCCER_LAYER_CONTROL_PENALTYOFFENSIVE_H

#include "layer/control/robosoccerstate.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PenaltyOffensive : public RoboSoccerState
	{
	public:
		PenaltyOffensive(Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
						 Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
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