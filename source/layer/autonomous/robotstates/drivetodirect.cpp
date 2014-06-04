#include "layer/autonomous/robotstates/drivetodirect.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/time/stopwatch.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Logging;
using namespace std;

DriveToDirect::DriveToDirect(
		ControllableRobot &robot, const Pose &target, const Watch &watch,
		Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_precisionPosition(0.01),
	m_precisionOrientationInitial(0.4),
	m_precisionOrientationFinal(0.1),
	m_initialRotationReached(false),
	m_initialRotationStarted(false),
	m_positionReached(false),
	m_driveStarted(false),
	m_finalRotationReached(false),
	m_finalRotationStarted(false),
	m_target(target),
	m_watchDog(new StopWatch(watch))
{ }

DriveToDirect::~DriveToDirect()
{
	delete m_watchDog;
	m_watchDog = 0;
}

bool DriveToDirect::reachedTarget() const
{
	return false;
}

RobotState* DriveToDirect::nextState(bool)
{
	Compare comparePosition(m_precisionPosition);
	Compare compareAngle(m_precisionOrientationFinal);
	Pose pose = getRobot().getPose();

	if (	(	comparePosition.isFuzzyEqual(pose.getPosition(), m_target.getPosition()) &&
				compareAngle.isFuzzyEqual(pose.getOrientation(), m_target.getOrientation())) ||
			 m_finalRotationReached)
		return new ReachedTarget(getRobot(), getLogger(), getLogFileType());
	else if (m_watchDog->getTime() > 10)
		return new ReachedTarget(getRobot(), getLogger(), getLogFileType());
	else
		return 0;
}

void DriveToDirect::updateInternal(bool movementStopped)
{
	Pose pose = getRobot().getPose();
	bool movementStopUsed = false;

	if (!m_initialRotationReached)
	{
		Compare compareAngle(m_precisionOrientationInitial);
		Angle targetAngle(pose.getPosition(), m_target.getPosition());
		if (compareAngle.isFuzzyEqual(pose.getOrientation(), targetAngle))
		{
			log("inital rotation reached");
			m_initialRotationReached = true;
			movementStopUsed = true;
		}
		else if (movementStopped)
		{
			log("inital rotation not really reached, but movement stopped");
			movementStopUsed = true;
			m_initialRotationReached = true;
		}
		else
		{
			if (!m_initialRotationStarted)
				getRobot().turn(targetAngle);

			m_initialRotationStarted = true;
			return;
		}
	}

	if (!m_positionReached)
	{
		Compare comparePosition(m_precisionPosition);
		if ((comparePosition.isFuzzyEqual(pose.getPosition(), m_target.getPosition())))
		{
			log("position reached");
			m_positionReached = true;
			movementStopUsed = true;
		}
		else if (movementStopped && !movementStopUsed)
		{
			log("position not really reached, but movement stopped");
			movementStopUsed = true;
			m_positionReached = true;
		}
		else
		{
			if (!m_driveStarted)
				getRobot().gotoPositionPrecise(m_target.getPosition());

			m_driveStarted = true;
			return;
		}
	}

	if (!m_finalRotationReached)
	{
		Compare compareAngle(m_precisionOrientationFinal);
		if (compareAngle.isFuzzyEqual(pose.getOrientation(), m_target.getOrientation()))
		{
			log("final rotation reached");
			m_finalRotationReached = true;
			movementStopUsed = true;
		}
		else if (movementStopped && !movementStopUsed)
		{
			log("final rotation not really reached, but movement stopped");
			movementStopUsed = true;
			m_finalRotationReached = true;
		}
		else
		{
			if (!m_finalRotationStarted)
				getRobot().turn(m_target.getOrientation());

			m_finalRotationStarted = true;
			return;
		}
	}
}

string DriveToDirect::getName() const
{
	return string("drive to direct");
}

bool DriveToDirect::isEquivalentToDriveToDirect(const Pose &target) const
{
	Compare comparePosition(m_precisionPosition);
	Compare compareAngle(m_precisionOrientationInitial);

	return	comparePosition.isFuzzyEqual(m_target.getPosition(), target.getPosition()) &&
			compareAngle.isFuzzyEqual(m_target.getOrientation(), target.getOrientation());
}

bool DriveToDirect::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}
