#ifndef ROBOSOCCER_LAYER_ABSTRACTION_REFEREEIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_REFEREEIMPL_H

#include "layer/abstraction/referee.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class RefereeImpl :
			public Referee
	{
	public:
		virtual FieldSide getOwnFieldSide() const;
	};
}
}
}

#endif


