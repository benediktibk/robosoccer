#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYDEFENSIVE_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYDEFENSIVE_H

#include "layer/control/robosoccerstate.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PreparePenaltyDefensive :
			public RoboSoccerState
	{
	public:
		PreparePenaltyDefensive(
				Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
				Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
				Autonomous::IntelligentBall const &ball,
				Autonomous::TargetPositionFetcher const &targetPositionFetcher,
				Abstraction::FieldPositionCheckerGoalkeeper &fieldPositionCheckerGoalKeeper);

		virtual Common::States::State* nextState();
		virtual std::string getName();

	private:
		virtual void updateInternal();

	private:
		bool m_movementFinished;
		bool m_sendGoToSignal;
	};
}
}
}

#endif
