#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFF_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFF_H

#include "layer/control/robosoccerstate.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PrepareKickOff :
			public RoboSoccerState
	{
	public:
		PrepareKickOff(
				Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
				Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
				Autonomous::IntelligentBall const &ball,
				const Autonomous::TargetPositionFetcher &targetPositionFetcher,
				Abstraction::FieldPositionCheckerGoalkeeper &fieldPositionCheckerGoalKeeper);

		virtual Common::States::State* nextState();
		virtual std::string getName();

	private:
		virtual void updateInternal();
	};
}
}
}

#endif


