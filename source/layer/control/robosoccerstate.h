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

namespace Control
{
	class RoboSoccerState : public Common::States::State
	{
	public:
		RoboSoccerState(Common::Logging::Logger &logger, Abstraction::RefereeBase &referee, bool callUpdateOnlyOnce);

	protected:
		Abstraction::RefereeBase &m_referee;
	};
}
}
}

#endif


