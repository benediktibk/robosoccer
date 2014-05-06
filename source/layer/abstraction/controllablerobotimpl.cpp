#include "layer/abstraction/controllablerobotimpl.h"
#include "layer/abstraction/robotturncontrol.h"
#include "layer/abstraction/robotdrivecontrol.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"
#include "common/geometry/angle.h"
#include "common/geometry/point.h"
#include <assert.h>
#include <kogmo_rtdb.hxx>
#include <robo_control.h>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common;
using namespace RoboSoccer::Common::Time;

ControllableRobotImpl::ControllableRobotImpl(
		unsigned int deviceId, KogniMobil::RTDBConn &dataBase, TeamColor color, Watch const &watch) :
	m_turnControl(new RobotTurnControl(watch)),
	m_driveControl(new RobotDriveControl(watch))
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
	delete m_turnControl;
	m_turnControl = 0;
	delete m_driveControl;
	m_driveControl = 0;
}

Geometry::Pose ControllableRobotImpl::getPose() const
{
	Geometry::Point position = getPosition();
	Geometry::Angle orientation = getOrientation();
	return Geometry::Pose(position, orientation);
}

Geometry::Circle ControllableRobotImpl::getObstacle() const
{
	Geometry::Pose pose = getPose();
	return Geometry::Circle(pose.getPosition(),0.095);
}

void ControllableRobotImpl::gotoPositionImprecise(const Geometry::Point &position)
{
	m_driveTarget = position;
	switchInto(StateDriving);
}

void ControllableRobotImpl::gotoPositionPrecise(const Geometry::Point &position)
{
	m_driveTarget = position;
	switchInto(StateDriving);
}

bool ControllableRobotImpl::kick(unsigned int force)
{
	assert(force <= 100);
	// the second param should not be set 0, despite the documentation says something different
	m_robot->Kick(force, 0.24);
	return false;
}

//! turns to an absolute angle
void ControllableRobotImpl::turn(const Geometry::Angle &absoluteAngle)
{
	m_turnTarget = absoluteAngle;
	switchInto(StateTurning);
}

void ControllableRobotImpl::stop()
{
	switchInto(StateStop);
}

void ControllableRobotImpl::update()
{
	double translationSpeed = 0;
	double rotationSpeed = 0;

	switch(m_state)
	{
	case StateStop:
		m_robot->StopAction();
		return;
	case StateTurning:
		rotationSpeed = m_turnControl->evaluate(getOrientation(), m_turnTarget);
		break;
	case StateDriving:
		m_driveControl->evaluate(getPose(), m_driveTarget, translationSpeed, rotationSpeed);
		break;
	}

	m_robot->setSpeed(translationSpeed, rotationSpeed, RoboControl::FORWARD);
}

Geometry::Angle ControllableRobotImpl::getOrientation() const
{
	Angle angle = m_robot->GetPhi();
	return Geometry::Angle(angle.Rad());
}

Geometry::Point ControllableRobotImpl::getPosition() const
{
	return Geometry::Point(m_robot->GetX(), m_robot->GetY());
}

void ControllableRobotImpl::switchInto(ControllableRobotImpl::State state)
{
	m_turnControl->reset();
	m_state = state;
}
