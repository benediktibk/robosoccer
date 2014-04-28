#ifndef ROBOSOCCER_LAYER_CONTROL_PAUSE_H
#define ROBOSOCCER_LAYER_CONTROL_PAUSE_H

#include "layer/control/robosoccerstate.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class Pause : public RoboSoccerState
	{
	public:
		Pause(Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee);

		virtual Common::States::State* nextState();
		virtual std::string getName();

	private:
		virtual void updateInternal();
	};
}
}
}

#endif


