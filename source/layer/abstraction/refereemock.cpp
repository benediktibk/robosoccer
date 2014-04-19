#include "layer/abstraction/refereemock.h"

using namespace RoboSoccer::Layer::Abstraction;

FieldSide RefereeMock::getOwnFieldSide()
{
	return FieldSideLeft;
}
