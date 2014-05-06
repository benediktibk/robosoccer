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
	return Geometry::Pose(Geometry::Point(m_robot->GetX(),m_robot->GetY()),m_robot->GetPhi().Rad());
}

Geometry::Circle ReadableRobotImpl::getObstacle() const
{
	return Geometry::Circle(getPose().getPosition(),0.095);
}

