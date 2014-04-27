#ifndef ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFDEFENSIVE_H
#define ROBOSOCCER_LAYER_CONTROL_PREPAREKICKOFFDEFENSIVE_H

#include "layer/control/robosoccerstate.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class PrepareKickOffDefensive :
			public RoboSoccerState
	{
	public:
		PrepareKickOffDefensive(Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee);

		virtual Common::States::State* nextState();
		virtual std::string getName();

	private:
		virtual void updateInternal();
	};
}
}
}

#endif


