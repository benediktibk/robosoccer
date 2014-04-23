#ifndef ROBOSOCCER_LAYER_ABSTRACTION_REFEREEMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_REFEREEMOCK_H

#include "layer/abstraction/referee.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class RefereeMock :
			public Referee
	{
	public:
		virtual FieldSide getOwnFieldSide() const;
	};
}
}
}

#endif


