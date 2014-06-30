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
	m_driveShortControl(new RobotDriveControl(watch, 0.4, 0.2, 500, 0, 40)),
	m_driveLongControl(new RobotDriveControl(watch, 0.2, 0.05, 200, 0, 120)),
	m_state(StateStop),
	m_translationSpeed(0),
	m_rotationSpeed(0),
	m_loopTimeWatch(new StopWatch(watch)),
	m_isDrivingFoward(true),
	m_watchDogEnd(new StopWatch(watch)),
	m_watchDogRestart(new StopWatch(watch)),
	m_logger(logger),
	m_logFileType(Logger::LogFileTypeInvalid),
	m_turnStarted(false),
	m_distanceForGoTo(0),
	m_timeWatchDogRestart(0.5)
{
	unsigned int modifiedDeviceId = deviceId;
	if (color == TeamColorRed)
		modifiedDeviceId += 3;
	assert(modifiedDeviceId <= 5);
	m_robot = new RoboControl(dataBase, modifiedDeviceId);

	switch(deviceId)
	{
	case 0:
		m_logFileType = Logger::LogFileTypeControllableRobotGoalkeeper;
		log("logging controllable goalie");
		break;
	case 1:
		m_logFileType = Logger::LogFileTypeControllableRobotOne;
		log("logging controllable robot one");
		break;
	case 2:
		m_logFileType = Logger::LogFileTypeControllableRobotTwo;
		log("logging controllable robot two");
		break;
	default:
		assert(false);
	}

	m_watchDogRestart->restart(m_timeWatchDogRestart);
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
	delete m_watchDogEnd;
	m_watchDogEnd = 0;
	delete m_watchDogRestart;
	m_watchDogRestart = 0;
}

Geometry::Pose ControllableRobotImpl::getPose() const
{
	return m_pose;
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
	return Geometry::Circle(pose.getPosition(), ReadableRobot::getWidth());
}

void ControllableRobotImpl::gotoPositionImprecise(const Geometry::Point &position)
{
	logPosition("current position", getPosition());
	logPosition("target for drive long", position);

	determineIsDrivingForwardForGoTo(position);
	m_driveTarget = position;
	m_distanceForGoTo = getPosition().distanceTo(position);
	switchInto(StateDrivingLong);
}

void ControllableRobotImpl::gotoPositionPrecise(const Geometry::Point &position)
{
	logPosition("current position", getPosition());
	logPosition("target for drive short", position);

	determineIsDrivingForwardForGoTo(position);
	m_driveTarget = position;
	m_distanceForGoTo = getPosition().distanceTo(position);
	switchInto(StateDrivingShort);
}

void ControllableRobotImpl::kick(Geometry::Point const &ballPosition)
{
	determineIsDrivingForwardForGoTo(ballPosition);
	switchInto(StateKick);
}

//! turns to an absolute angle
void ControllableRobotImpl::turn(const Geometry::Angle &absoluteAngle)
{
	logOrientation("current orientation", getOrientation());
	logOrientation("target for turning", absoluteAngle);

	determineIsDrivingForwardForTurning(absoluteAngle);

	if (m_isDrivingFoward)
		m_turnTarget = absoluteAngle;
	else
		m_turnTarget = absoluteAngle + Geometry::Angle::getHalfRotation().getValueBetweenMinusPiAndPi();

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
	bool watchDogTurningEnd = m_watchDogEnd->getTime() > 0.5;
	bool watchDogKickingEnd = m_watchDogEnd->getTime() > 0.3;
	const double speedInDrivingShort = 0.1;
	const double speedInDrivingLong = 0.5;
	bool watchDogDrivingShortEnd = m_watchDogEnd->getTime() > m_distanceForGoTo/speedInDrivingShort;
	bool watchDogDrivingLongEnd = m_watchDogEnd->getTime() > m_distanceForGoTo/speedInDrivingLong;
	bool watchDogRestart = m_watchDogRestart->getTime() > m_timeWatchDogRestart;

	Geometry::Point position(m_robot->GetX(), m_robot->GetY());
	Geometry::Angle orientation(m_robot->GetPhi().Rad());
	if (fabs(position.getX())<3 || fabs(position.getY())<3)
		m_pose =  Geometry::Pose(position, orientation);

	switch(m_state)
	{
	case StateStop:
		m_robot->StopAction();
		return;
	case StateTurning:
		if (watchDogRestart && !m_turnStarted)
		{
			m_robot->TurnAbs(Angle(m_turnTarget.getValueBetweenMinusPiAndPi()));
			logOrientation("set order to turn to", m_turnTarget);
			m_watchDogRestart->restart();
			m_turnStarted = true;
		}
		else if (orientationCompare.isFuzzyEqual(getOrientation(), m_turnTarget))
		{
			logOrientation("current orientation", getOrientation());
			log("reached target orientation");
			switchInto(StateStop);
		}
		else if (watchDogTurningEnd)
		{
			log("watch dog for turning");
			switchInto(StateStop);
		}
		return;
	case StateDrivingShort:
		if (watchDogDrivingShortEnd)
		{
			log("was not able to reach target, took too long");
			switchInto(StateStop);
		}
		else if(getPosition().distanceTo(m_driveTarget) > 0.01)
			m_driveShortControl->evaluate(getPose(), m_driveTarget, translationSpeed, rotationSpeed);
		else
		{
			logPosition("current position", getPosition());
			log("reachted target position");
			switchInto(StateStop);
		}
		break;
	case StateDrivingLong:
		if (watchDogDrivingLongEnd)
		{
			log("was not able to reach target, took too long");
			switchInto(StateStop);
		}
		else if(getPosition().distanceTo(m_driveTarget) > 0.01)
			m_driveLongControl->evaluate(getPose(), m_driveTarget, translationSpeed, rotationSpeed);
		else
		{
			logPosition("current position", getPosition());
			log("reachted target position");
			switchInto(StateStop);
		}
		break;
	case StateKick:
		if (watchDogKickingEnd)
		{
			log("watch dog for kicking");
			switchInto(StateStop);
		}
		else
		{
			translationSpeed = 200;
			rotationSpeed = 0;
		}
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
	return m_pose.getPosition();
}

void ControllableRobotImpl::switchInto(ControllableRobotImpl::State state)
{
	if (m_state != state)
		logState(state);

	m_driveShortControl->reset(getPose());
	m_driveLongControl->reset(getPose());
	m_state = state;
	m_watchDogEnd->restart();
	m_turnStarted = false;
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

void ControllableRobotImpl::determineIsDrivingForwardForGoTo(const Geometry::Point &target)
{
	Geometry::Angle absoluteAngleToTarget(getPosition(), target);
	Geometry::Angle relativeAngleToTarget = absoluteAngleToTarget - getOrientationRaw();
	bool previousIsDrivingForward = m_isDrivingFoward;
	m_isDrivingFoward = fabs(relativeAngleToTarget.getValueBetweenMinusPiAndPi()) < Geometry::Angle::getQuarterRotation().getValueBetweenMinusPiAndPi();

	if (previousIsDrivingForward != m_isDrivingFoward)
		logIsDrivingForward();
}

Geometry::Angle ControllableRobotImpl::getOrientationRaw() const
{
	return m_pose.getOrientation();
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
	m_logger.logToLogFileOfType(m_logFileType, message);
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

void ControllableRobotImpl::determineIsDrivingForwardForTurning(const Geometry::Angle &target)
{
	Geometry::Angle relativeAngle = target - getOrientationRaw();
	bool previousIsDrivingForward = m_isDrivingFoward;
	m_isDrivingFoward = fabs(relativeAngle.getValueBetweenMinusPiAndPi()) < Geometry::Angle::getQuarterRotation().getValueBetweenMinusPiAndPi();

	if (previousIsDrivingForward != m_isDrivingFoward)
		logIsDrivingForward();
}

void ControllableRobotImpl::logIsDrivingForward()
{
	if (m_isDrivingFoward)
		log("switching to drive forward");
	else
		log("switching to drive backward");
}
