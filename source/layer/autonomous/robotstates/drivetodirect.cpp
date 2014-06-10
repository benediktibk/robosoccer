#include "layer/autonomous/robotstates/drivetodirect.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;


DriveToDirect::DriveToDirect(
		ControllableRobot &robot, const Pose &target, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_target(target),
	m_precisionInitialRotation(0.4),
	m_precisionDriving(0.01),
	m_precisionFinalRotation(0.1),
	m_movementStarted(false)
{ }

bool DriveToDirect::reachedTarget() const
{
	return false;
}

bool DriveToDirect::isEquivalentToDriveToDirect(const Pose &target) const
{
	Compare positionCompare(m_precisionDriving);
	Compare rotationCompare(m_precisionFinalRotation);
	return	positionCompare.isFuzzyEqual(m_target.getPosition(), target.getPosition()) &&
			rotationCompare.isFuzzyEqual(m_target.getOrientation(), target.getOrientation());
}

bool DriveToDirect::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}

void DriveToDirect::update()
{
	if (m_movementStarted)
		return;

	updateInternal();
	m_movementStarted = true;
}

const Pose &DriveToDirect::getTarget() const
{
	return m_target;
}

double DriveToDirect::getPrecisionInitialRotation() const
{
	return m_precisionInitialRotation;
}

double DriveToDirect::getPrecisionDriving() const
{
	return m_precisionDriving;
}

double DriveToDirect::getPrecisionFinalRotation() const
{
	return m_precisionFinalRotation;
}

bool DriveToDirect::hasMovementStarted() const
{
	return m_movementStarted;
}
