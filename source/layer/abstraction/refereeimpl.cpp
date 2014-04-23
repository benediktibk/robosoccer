#include "layer/abstraction/refereeimpl.h"

using namespace RoboSoccer::Layer::Abstraction;

FieldSide RefereeImpl::getOwnFieldSide() const
{
	return FieldSideLeft;
}
