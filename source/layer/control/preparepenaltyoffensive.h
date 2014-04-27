#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYOFFENSIVE_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREPENALTYOFFENSIVE_H

#include "layer/control/robosoccerstate.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PreparePenaltyOffensive :
			public RoboSoccerState
	{
	public:
		PreparePenaltyOffensive(Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee);

		virtual Common::States::State* nextState();
		virtual std::string getName();

	private:
		virtual void updateInternal();
	};
}
}
}

#endif


