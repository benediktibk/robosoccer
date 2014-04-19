#include "layer/abstraction/controllablerobotimpl.h"
#include "common/geometry/orientedposition.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

ControllableRobotImpl::ControllableRobotImpl()
{ }

OrientedPosition ControllableRobotImpl::getPosition()
{
	return OrientedPosition();
}

Circle ControllableRobotImpl::createObstacle()
{
	return Circle();
}

void ControllableRobotImpl::gotoPositionImprecise(const Point &/*position*/)
{

}

void ControllableRobotImpl::gotoPositionPrecise(const Point &/*position*/)
{

}

bool ControllableRobotImpl::kick(unsigned int /*force*/, double /*distanceToBall*/)
{
	return false;
}

void ControllableRobotImpl::turn(const Angle &/*absoluteAngle*/)
{

}

