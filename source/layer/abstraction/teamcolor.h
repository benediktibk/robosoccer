#ifndef ROBOSOCCER_LAYER_ABSTRACTION_TEAMCOLOR_H
#define ROBOSOCCER_LAYER_ABSTRACTION_TEAMCOLOR_H

#include <ostream>

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	enum TeamColor
	{
		TeamColorBlue,
		TeamColorRed
	};
}
}
}

std::ostream& operator<<(std::ostream &stream, const RoboSoccer::Layer::Abstraction::TeamColor &teamColor);

#endif