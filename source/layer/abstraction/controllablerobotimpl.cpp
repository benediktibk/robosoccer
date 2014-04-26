#include "layer/abstraction/controllablerobotimpl.h"
#include "common/geometry/orientedposition.h"
#include "common/geometry/circle.h"
#include <assert.h>
#include <kogmo_rtdb.hxx>
#include <robo_control.h>
#include "common/geometry/angle.h"
#include "common/geometry/point.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common;

ControllableRobotImpl::ControllableRobotImpl()
{ }

Geometry::OrientedPosition ControllableRobotImpl::getPosition() const
{
	Geometry::Point robotPosition;
	robotPosition.setX(m_robot->GetX());
	robotPosition.setY(m_robot->GetY());
	Angle angle = m_robot->GetPhi();
	Geometry::Angle robotAngle(angle.Rad());
	return Geometry::OrientedPosition(robotPosition,robotAngle);
}

Geometry::Circle ControllableRobotImpl::createObstacle() const
{
	Geometry::OrientedPosition pose = getPosition();
	return Geometry::Circle(pose.getPosition(),0.095);
}

void ControllableRobotImpl::gotoPositionImprecise(const Geometry::Point &/*position*/)
{

}

void ControllableRobotImpl::gotoPositionPrecise(const Geometry::Point &/*position*/)
{

}

bool ControllableRobotImpl::kick(unsigned int force, double distanceToBall)
{
	assert(force <= 100);
	assert(distanceToBall >= 0);
	return false;
}

void ControllableRobotImpl::turn(const Geometry::Angle &/*absoluteAngle*/)
{

}

