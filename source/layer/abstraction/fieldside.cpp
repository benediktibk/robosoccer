#include "layer/abstraction/fieldside.h"

using namespace RoboSoccer::Layer::Abstraction;

std::ostream& operator<<(std::ostream &stream, const FieldSide &fieldSide)
{
	switch(fieldSide)
	{
	case FieldSideLeft:
		stream << "left";
		break;
	case FieldSideRight:
		stream << "right";
		break;
	case FieldSideInvalid:
		stream << "invalid";
		break;
	}

	return stream;
}
