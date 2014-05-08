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

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common;
using namespace RoboSoccer::Common::Time;

ControllableRobotImpl::ControllableRobotImpl(
		unsigned int deviceId, KogniMobil::RTDBConn &dataBase, TeamColor color, Watch const &watch) :
	m_driveShortControl(new RobotDriveControl(watch, 0.2, 0.2, 50, 40)),
	m_driveLongControl(new RobotDriveControl(watch, 0.1, 0.05, 50, 40)),
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
	m_robot->TurnAbs(Angle(absoluteAngle.getValueBetweenMinusPiAndPi()));
	switchInto(StateTurning);
}

void ControllableRobotImpl::drive(const Geometry::Point &targetPoint)
{
	m_driveTarget = targetPoint;
	switchInto(StateDrivingShort);
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
		return;
	case StateDrivingShort:
		if(getPosition().distanceTo(m_driveTarget) > 0.01)
			m_driveShortControl->evaluate(getPose(), m_driveTarget, translationSpeed, rotationSpeed);
		else
			switchInto(StateStop);
		break;
	case StateDrivingLong:
		if(getPosition().distanceTo(m_driveTarget) > 0.1)
			m_driveLongControl->evaluate(getPose(), m_driveTarget, translationSpeed, rotationSpeed);
		else
			switchInto(StateStop);
		break;
	}

	setSpeed(translationSpeed, rotationSpeed);
}

void ControllableRobotImpl::measure()
{
	Geometry::Point position(m_robot->GetX(), m_robot->GetY());
	Geometry::Angle orientation(m_robot->GetPhi().Rad());
	double loopTime = m_loopTimeWatch->getTimeAndRestart();

	/*!
	 * If the new values are exactly the same like the ones we have received
	 * last, it is very likely that no new frame arrived. In this case we will
	 * extrapolate the position and orientation.
	 */
	if (	position == m_lastPoseReceived.getPosition() &&
			orientation == m_lastPoseReceived.getOrientation())
	{
		//! @todo extrapolate position
		double rotationSpeedTransformed = m_rotationSpeed*6.8;
		Geometry::Angle rotationChange(rotationSpeedTransformed*loopTime);
		m_currentPose.setOrientation(getOrientation() + rotationChange);
	}
	else
	{
		m_currentPose = Geometry::Pose(position, orientation);
		m_lastPoseReceived = m_currentPose;
	}
}

Geometry::Angle ControllableRobotImpl::getOrientation() const
{
	return m_currentPose.getOrientation();
}

Geometry::Point ControllableRobotImpl::getPosition() const
{
	return m_currentPose.getPosition();
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
	m_robot->setSpeed(translationSpeed, rotationSpeed, RoboControl::FORWARD);
}
