#include "layer/abstraction/controllablerobotimpl.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"
#include <assert.h>
#include <kogmo_rtdb.hxx>
#include <robo_control.h>
#include "common/geometry/angle.h"
#include "common/geometry/point.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common;

ControllableRobotImpl::ControllableRobotImpl(unsigned int deviceId, KogniMobil::RTDBConn &dataBase, TeamColor color)
{
	if (color == TeamColorRed)
		deviceId += 3;
	assert(deviceId <= 5);
	m_robot = new RoboControl(dataBase,deviceId);
}

ControllableRobotImpl::~ControllableRobotImpl()
{
	delete m_robot;
	m_robot = 0;
}

Geometry::Pose ControllableRobotImpl::getPose() const
{
	Geometry::Point robotPosition;
	robotPosition.setX(m_robot->GetX());
	robotPosition.setY(m_robot->GetY());
	Angle angle = m_robot->GetPhi();
	Geometry::Angle robotAngle(angle.Rad());
	return Geometry::Pose(robotPosition,robotAngle);
}

Geometry::Circle ControllableRobotImpl::createObstacle() const
{
	Geometry::Pose pose = getPose();
	return Geometry::Circle(pose.getPosition(),0.095);
}

void ControllableRobotImpl::gotoPositionImprecise(const Geometry::Point &position)
{
	m_robot->GotoXY(position.getX(),position.getY(),160,false);
}

void ControllableRobotImpl::gotoPositionPrecise(const Geometry::Point &position)
{
	m_robot->GotoXY(position.getX(),position.getY(),160,true);
}

bool ControllableRobotImpl::kick(unsigned int force)
{
	assert(force <= 100);
	m_robot->Kick(force, 0.24);
	return false;
}

void ControllableRobotImpl::turn(const Geometry::Angle &absoluteAngle)
{
	double value = absoluteAngle.getValueBetweenZeroAndTwoPi();
	m_robot->TurnAbs(value);
}

void ControllableRobotImpl::stop()
{
	m_robot->StopAction();
}

