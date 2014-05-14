#include "layer/abstraction/controllablerobotimpl.h"
#include "layer/abstraction/robotdrivecontrol.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"
#include "common/geometry/angle.h"
#include "common/geometry/point.h"
#include "common/geometry/compare.h"
#include "common/time/stopwatch.h"
#include "common/logging/logger.h"
#include <assert.h>
#include <kogmo_rtdb.hxx>
#include <robo_control.h>
#include <math.h>
#include <sstream>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Logging;

ControllableRobotImpl::ControllableRobotImpl(
		unsigned int deviceId, KogniMobil::RTDBConn &dataBase, TeamColor color, Watch const &watch, Common::Logging::Logger &logger) :
	m_driveShortControl(new RobotDriveControl(watch, 0.3, 0.2, 50, 0, 40)),
	m_driveLongControl(new RobotDriveControl(watch, 0.1, 0.05, 200, 0, 120)),
	m_translationSpeed(0),
	m_rotationSpeed(0),
	m_loopTimeWatch(new StopWatch(watch)),
	m_isDrivingFoward(true),
	m_watchDog(new StopWatch(watch)),
	m_logger(logger),
	m_deviceId(deviceId)
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
	delete m_watchDog;
	m_watchDog = 0;
}

Geometry::Pose ControllableRobotImpl::getPose() const
{
	Geometry::Point position = getPosition();
	Geometry::Angle orientation = getOrientation();
	return Geometry::Pose(position, orientation);
}

Geometry::Pose ControllableRobotImpl::getPoseRaw() const
{
	Geometry::Point position = getPosition();
	Geometry::Angle orientation = getOrientationRaw();
	return Geometry::Pose(position, orientation);
}

Geometry::Circle ControllableRobotImpl::getObstacle() const
{
	Geometry::Pose pose = getPose();
	return Geometry::Circle(pose.getPosition(), 0.095);
}

void ControllableRobotImpl::gotoPositionImprecise(const Geometry::Point &position)
{
	determineIsDrivingForward(position);
	m_driveTarget = position;
	switchInto(StateDrivingLong);
	logPosition("current position", getPosition());
	logPosition("target for drive long", position);
}

void ControllableRobotImpl::gotoPositionPrecise(const Geometry::Point &position)
{
	determineIsDrivingForward(position);
	m_driveTarget = position;
	switchInto(StateDrivingShort);
	logPosition("current position", getPosition());
	logPosition("target for drive short", position);
}

void ControllableRobotImpl::kick(unsigned int force)
{
	assert(force <= 100);
	// the second param should not be set 0, despite the documentation says something different
	m_robot->Kick(force, 0.24);
	switchInto(StateKick);
}

//! turns to an absolute angle
void ControllableRobotImpl::turn(const Geometry::Angle &absoluteAngle)
{
	Geometry::Angle relativeAngle = absoluteAngle - getOrientationRaw();

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

	m_robot->TurnAbs(Angle(m_turnTarget.getValueBetweenMinusPiAndPi()));
	switchInto(StateTurning);
	logOrientation("current orientation", getOrientation());
	logOrientation("target for turning", absoluteAngle);
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
	bool watchDogTurning = m_watchDog->getTime() > 0.5;
	bool watchDogKicking = m_watchDog->getTime() > 1;

	switch(m_state)
	{
	case StateStop:
		m_robot->StopAction();
		return;
	case StateTurning:
		if (orientationCompare.isFuzzyEqual(getOrientation(), m_turnTarget))
		{
			logOrientation("current orientation", getOrientation());
			log("reached target orientation");
			switchInto(StateStop);
		}
		else if (watchDogTurning)
		{
			log("watch dog for turning");
			switchInto(StateStop);
		}
		return;
	case StateDrivingShort:
		if(getPosition().distanceTo(m_driveTarget) > 0.01)
			m_driveShortControl->evaluate(getPose(), m_driveTarget, translationSpeed, rotationSpeed);
		else
		{
			logPosition("current position", getPosition());
			log("reachted target position");
			switchInto(StateStop);
		}
		break;
	case StateDrivingLong:
		if(getPosition().distanceTo(m_driveTarget) > 0.01)
			m_driveLongControl->evaluate(getPose(), m_driveTarget, translationSpeed, rotationSpeed);
		else
		{
			logPosition("current position", getPosition());
			log("reachted target position");
			switchInto(StateStop);
		}
		break;
	case StateKick:
		if (watchDogKicking)
		{
			log("watch dog for kicking");
			switchInto(StateStop);
		}
		return;
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
	case StateKick:
		return true;
	}

	// make the compiler happy
	assert(false);
	return true;
}

Geometry::Angle ControllableRobotImpl::getOrientation() const
{
	if(m_isDrivingFoward)
		return getOrientationRaw();
	else
		return getOrientationRaw() + Geometry::Angle::getHalfRotation();
}

Geometry::Point ControllableRobotImpl::getPosition() const
{
	return Geometry::Point(m_robot->GetX(), m_robot->GetY());
}

void ControllableRobotImpl::switchInto(ControllableRobotImpl::State state)
{
	if (m_state != state)
		logState(state);

	m_driveShortControl->reset(getPose());
	m_driveLongControl->reset(getPose());
	m_state = state;
	m_watchDog->getTimeAndRestart();
}

void ControllableRobotImpl::setSpeed(double translationSpeed, double rotationSpeed)
{
	m_translationSpeed = translationSpeed;
	m_rotationSpeed = rotationSpeed;
	if(m_isDrivingFoward)
		m_robot->setSpeed(translationSpeed, rotationSpeed, RoboControl::FORWARD);
	else
		m_robot->setSpeed(translationSpeed, rotationSpeed, RoboControl::BACKWARD);
}

void ControllableRobotImpl::determineIsDrivingForward(const Geometry::Point &target)
{
	Geometry::Angle relativeAngleToTarget(getPosition(), target);
	m_isDrivingFoward = fabs(relativeAngleToTarget.getValueBetweenMinusPiAndPi()) < Geometry::Angle::getQuarterRotation().getValueBetweenMinusPiAndPi();
}

Geometry::Angle ControllableRobotImpl::getOrientationRaw() const
{
	return Geometry::Angle(m_robot->GetPhi().Rad());
}

void ControllableRobotImpl::logState(State state)
{
	stringstream stream;
	stream << "switching into state ";

	switch(state)
	{
	case StateStop:
		stream << "stop";
		break;
	case StateTurning:
		stream << "turning";
		break;
	case StateDrivingShort:
		stream << "driving short";
		break;
	case StateDrivingLong:
		stream << "driving long";
		break;
	case StateKick:
		stream << "kicking";
		break;
	}

	log(stream.str());
}

void ControllableRobotImpl::log(const string &message)
{
	Logger::LogFileType fileType = Logger::LogFileTypeInvalid;

	switch(m_deviceId)
	{
	case 0:
		fileType = Logger::LogFileTypeRobotGoalkeeperPositions;
		break;
	case 1:
		fileType = Logger::LogFileTypeRobot1Positions;
		break;
	case 2:
		fileType = Logger::LogFileTypeRobot2Positions;
		break;
	default:
		assert(false);
	}

	m_logger.logToLogFileOfType(fileType, message);
}

void ControllableRobotImpl::logPosition(string const &message, const Geometry::Point &position)
{
	stringstream stream;
	stream << message << ": " << position;
	log(stream.str());
}

void ControllableRobotImpl::logOrientation(string const &message, const Geometry::Angle &orientation)
{
	stringstream stream;
	stream << message << ": " << orientation;
	log(stream.str());
}
