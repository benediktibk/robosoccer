#include "layer/abstraction/refereemock.h"

using namespace RoboSoccer::Layer::Abstraction;

FieldSide RefereeMock::getOwnFieldSide() const
{
	return FieldSideLeft;
}
