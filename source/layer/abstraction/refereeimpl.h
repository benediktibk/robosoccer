#ifndef ROBOSOCCER_LAYER_ABSTRACTION_REFEREEIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_REFEREEIMPL_H

#include "layer/abstraction/refereebase.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class RefereeImpl :
			public RefereeBase
	{
	public:
		virtual FieldSide getOwnFieldSide() const;
	};
}
}
}

#endif


