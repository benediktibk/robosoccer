#include "layer/abstraction/readablerobotimpl.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"
#include <kogmo_rtdb.hxx>
#include <robo_control.h>
#include <assert.h>
#include "common/geometry/angle.h"
#include "common/geometry/point.h"
#include <math.h>

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
	assert(fabs(m_pose.getPosition().getX()) < 5 || fabs(m_pose.getPosition().getY()) < 5);
	return Geometry::Pose(m_pose.getPosition(),m_pose.getOrientation());
}

Geometry::Circle ReadableRobotImpl::getObstacle() const
{
	return Geometry::Circle(getPose().getPosition(),ReadableRobot::getWidth());
}

void ReadableRobotImpl::updateSensors()
{
	Geometry::Point position(m_robot->GetX(), m_robot->GetY());
	Geometry::Angle orientation(m_robot->GetPhi().Rad());
	if (fabs(position.getX())<3 || fabs(position.getY())<3)
		m_pose =  Geometry::Pose(position, orientation);
}
