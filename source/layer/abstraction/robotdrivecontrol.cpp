#include "layer/abstraction/robotdrivecontrol.h"
#include "common/other/pidcontroller.h"
#include "common/geometry/pose.h"
#include "common/geometry/point.h"
#include <math.h>
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common;
using namespace RoboSoccer::Common::Geometry;

RobotDriveControl::RobotDriveControl(
		const Watch& watch,
		double rotationP, double rotationI,
		double forwardP, double forwardI,
		double minSpeed) :
  m_rotationController(new Other::PIDController(rotationP, rotationI, 0, watch)),
  m_translationController(new Other::PIDController(forwardP, forwardI, 0, watch)),
  m_minSpeed(minSpeed)
{ }

RobotDriveControl::~RobotDriveControl()
{
  delete m_rotationController;
  m_rotationController = 0;
  delete m_translationController;
  m_translationController = 0;
}

void RobotDriveControl::evaluate(const Pose& current, const Point& target, double& translationSpeed, double& rotationSpeed)
{
	Compare positionCompare(0.01);
	const Point &currentPosition = current.getPosition();
	Angle alpha = Angle(target, currentPosition, m_startPosition);
	Angle ownOrientation = current.getOrientation();
	Angle targetOrientation(currentPosition, target);
	Angle orientationDifference = targetOrientation - ownOrientation;
	double distanceToTarget = currentPosition.distanceTo(target);
	double orthogonalError = distanceToTarget*sin(orientationDifference.getValueBetweenMinusPiAndPi());
	double forwardError = std::max(0.0, distanceToTarget*cos(alpha.getValueBetweenMinusPiAndPi()));

	if (positionCompare.isFuzzyEqual(forwardError, 0) || alpha.isObtuse())
	{
		rotationSpeed = 0;
		translationSpeed = 0;
		return;
	}

  rotationSpeed = m_rotationController->evaluate(orthogonalError);
  translationSpeed = m_translationController->evaluate(forwardError);

  if (translationSpeed > 0)
  {
	  translationSpeed = std::max<double>(translationSpeed, getMinSpeed());
	  translationSpeed = std::min<double>(translationSpeed, 200);
  }
  else if (translationSpeed < 0)
  {
	  translationSpeed = std::max<double>(translationSpeed, -200);
	  translationSpeed = std::min<double>(translationSpeed, -getMinSpeed());
  }

  double magnitudeModification = 1 - fabs(rotationSpeed*2);
  if (magnitudeModification > 1)
	  magnitudeModification = 1;
  else if (magnitudeModification < 0)
	  magnitudeModification = 0;
  translationSpeed *= magnitudeModification;
}

void RobotDriveControl::reset(const Pose &start)
{
  m_startPosition = start.getPosition();
  m_translationController->resetTo(0);
  m_rotationController->resetTo(0);
}

double RoboSoccer::Layer::Abstraction::RobotDriveControl::getMinSpeed() const
{
	return m_minSpeed;
}
