#include "layer/abstraction/readablerobotimpl.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"
#include <kogmo_rtdb.hxx>
#include <robo_control.h>
#include <assert.h>
#include "common/geometry/angle.h"
#include "common/geometry/point.h"


using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common;

ReadableRobotImpl::ReadableRobotImpl(unsigned int deviceId, KogniMobil::RTDBConn &dataBase, TeamColor color)
{
	if (color == TeamColorRed)
		deviceId += 3;
	assert(deviceId <= 5);
	m_robot = new RoboControl(dataBase,deviceId);
}
ReadableRobotImpl::~ReadableRobotImpl()
{
	delete m_robot;
	m_robot = 0;
}

Geometry::Pose ReadableRobotImpl::getPose() const
{
	Geometry::Point robotPosition;
	robotPosition.setX(m_robot->GetX());
	robotPosition.setY(m_robot->GetY());
	Angle angle = m_robot->GetPhi();
	Geometry::Angle robotAngle(angle.Rad());
	return Geometry::Pose(robotPosition,robotAngle);
}

Geometry::Circle ReadableRobotImpl::getObstacle() const
{
	Geometry::Pose pose = getPose();
	return Geometry::Circle(pose.getPosition(),0.095);
}

