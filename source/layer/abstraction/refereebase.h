#ifndef ROBOSOCCER_LAYER_ABSTRACTION_REFEREEBASE_H
#define ROBOSOCCER_LAYER_ABSTRACTION_REFEREEBASE_H

#include "layer/abstraction/fieldside.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class RefereeBase
	{
	public:
		virtual ~RefereeBase() {}

		virtual FieldSide getOwnFieldSide() const = 0;
	};
}
}
}

#endif


