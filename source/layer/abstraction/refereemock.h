#ifndef ROBOSOCCER_LAYER_ABSTRACTION_REFEREEMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_REFEREEMOCK_H

#include "layer/abstraction/refereebase.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class RefereeMock :
			public RefereeBase
	{
	public:
		virtual FieldSide getOwnFieldSide() const;
	};
}
}
}

#endif


