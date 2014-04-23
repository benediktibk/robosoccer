#ifndef ROBOSOCCER_LAYER_ABSTRACTION_REFEREE_H
#define ROBOSOCCER_LAYER_ABSTRACTION_REFEREE_H

#include "layer/abstraction/fieldside.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class Referee
	{
	public:
		virtual ~Referee() {}

		virtual FieldSide getOwnFieldSide() const = 0;
	};
}
}
}

#endif


