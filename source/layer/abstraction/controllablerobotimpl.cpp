#include "layer/abstraction/controllablerobotimpl.h"
#include "layer/abstraction/robotdrivecontrol.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"
#include "common/geometry/angle.h"
#include "common/geometry/point.h"
#include "common/geometry/compare.h"
#include "common/time/stopwatch.h"
#include <assert.h>
#include <kogmo_rtdb.hxx>
#include <robo_control.h>
#include <iostream>
#include <math.h>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common;
using namespace RoboSoccer::Common::Time;

ControllableRobotImpl::ControllableRobotImpl(
		unsigned int deviceId, KogniMobil::RTDBConn &dataBase, TeamColor color, Watch const &watch) :
	m_driveShortControl(new RobotDriveControl(watch, 0.3, 0.2, 50, 0, 40)),
	m_driveLongControl(new RobotDriveControl(watch, 0.1, 0.05, 200, 0, 120)),
	m_translationSpeed(0),
	m_rotationSpeed(0),
	m_loopTimeWatch(new StopWatch(watch))
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
	delete m_driveShortControl;
	m_driveShortControl = 0;
	delete m_driveLongControl;
	m_driveLongControl = 0;
	delete m_loopTimeWatch;
	m_loopTimeWatch = 0;
}

Geometry::Pose ControllableRobotImpl::getPose() const
{
	Geometry::Point position = getPosition();
	Geometry::Angle orientation = getOrientation();
	if(m_isDrivingFoward)
		return Geometry::Pose(position, orientation);
	else
		return Geometry::Pose(position, orientation + Geometry::Angle::getHalfRotation());
}

Geometry::Pose ControllableRobotImpl::getPoseRaw() const
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
	switchInto(StateDrivingLong);
}

void ControllableRobotImpl::gotoPositionPrecise(const Geometry::Point &position)
{
	m_driveTarget = position;
	switchInto(StateDrivingShort);
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
	Geometry::Angle relativeAngle = absoluteAngle - getPoseRaw().getOrientation();
	if (fabs(relativeAngle.getValueBetweenMinusPiAndPi()) > Geometry::Angle::getQuarterRotation().getValueBetweenMinusPiAndPi())
	{
		m_isDrivingFoward = false;
		m_turnTarget = absoluteAngle + Geometry::Angle::getHalfRotation().getValueBetweenMinusPiAndPi();
	}
	else
	{
		m_isDrivingFoward = true;
		m_turnTarget = absoluteAngle;
	}
	cout << "relative angle"<< m_isDrivingFoward << endl;
	m_robot->TurnAbs(Angle(m_turnTarget.getValueBetweenMinusPiAndPi()));
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
	Geometry::Compare orientationCompare(0.1);

	switch(m_state)
	{
	case StateStop:
		m_robot->StopAction();
		return;
	case StateTurning:
		if (orientationCompare.isFuzzyEqual(getOrientation(), m_turnTarget))
			switchInto(StateStop);
		return;
	case StateDrivingShort:
		if(getPosition().distanceTo(m_driveTarget) > 0.01)
			m_driveShortControl->evaluate(getPose(), m_driveTarget, translationSpeed, rotationSpeed);
		else
			switchInto(StateStop);
		break;
	case StateDrivingLong:
		if(getPosition().distanceTo(m_driveTarget) > 0.05)
			m_driveLongControl->evaluate(getPose(), m_driveTarget, translationSpeed, rotationSpeed);
		else
			switchInto(StateStop);
		break;
	}

	setSpeed(translationSpeed, rotationSpeed);
}

bool ControllableRobotImpl::isMoving() const
{
	switch(m_state)
	{
	case StateStop:
		return false;
	case StateTurning:
	case StateDrivingShort:
	case StateDrivingLong:
		return true;
	}

	// make the compiler happy
	assert(false);
	return true;
}

Geometry::Angle ControllableRobotImpl::getOrientation() const
{
	return Geometry::Angle(m_robot->GetPhi().Rad());
}

Geometry::Point ControllableRobotImpl::getPosition() const
{
	return Geometry::Point(m_robot->GetX(),m_robot->GetY());
}

void ControllableRobotImpl::switchInto(ControllableRobotImpl::State state)
{
	m_driveShortControl->reset(getPose());
	m_driveLongControl->reset(getPose());
	m_state = state;
}

void ControllableRobotImpl::setSpeed(double translationSpeed, double rotationSpeed)
{
	m_translationSpeed = translationSpeed;
	m_rotationSpeed = rotationSpeed;
	if(m_isDrivingFoward)
		m_robot->setSpeed(translationSpeed, rotationSpeed, RoboControl::FORWARD);
	else
		m_robot->setSpeed(translationSpeed, -rotationSpeed, RoboControl::BACKWARD);
}
