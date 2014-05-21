#ifndef ROBOSOCCER_LAYER_ABSTRACTION_FIELDSIDE_H
#define ROBOSOCCER_LAYER_ABSTRACTION_FIELDSIDE_H

#include <ostream>

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	enum FieldSide
	{
		FieldSideLeft,
		FieldSideRight,
		FieldSideInvalid
	};
}
}
}

std::ostream& operator<<(std::ostream &stream, const RoboSoccer::Layer::Abstraction::FieldSide &fieldSide);

#endif


