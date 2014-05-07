#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTY_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTY_H

#include "layer/control/robosoccerstate.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class UserInputFetcher;

	class PreparePenalty :
			public RoboSoccerState
	{
	public:
		PreparePenalty(Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
					   Autonomous::Team &ownTeam, Autonomous::EnemyTeam const &enemyTeam,
					   Autonomous::IntelligentBall const &ball,
					   Autonomous::TargetPositionFetcher const &targetPositionFetcher,
					   UserInputFetcher *userInputFetcher);
		virtual ~PreparePenalty();

		virtual Common::States::State* nextState();
		virtual std::string getName();

	private:
		virtual void updateInternal();

	private:
		UserInputFetcher *m_userInputFetcher;
	};
}
}
}

#endif


