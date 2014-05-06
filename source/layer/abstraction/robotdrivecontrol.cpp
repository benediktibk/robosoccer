#include "layer/abstraction/robotdrivecontrol.h"
#include "common/other/pidcontroller.h"
#include "common/geometry/pose.h"
#include "common/geometry/point.h"
#include <math.h>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Other;
using namespace RoboSoccer::Common::Geometry;

RobotDriveControl::RobotDriveControl(const Watch& watch) :
  m_rotationController(new PIDController(0.15, 0.1, 0, watch)),
  //m_translationController(new PIDController(30, 50, 0, watch))
  m_translationController(new PIDController(50, 25, 0, watch))
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
  Angle currentOrientation = current.getOrientation();
  Point currentPosition = current.getPosition();

  Angle targetOrientation(atan2(target.getY() - currentPosition.getY(), target.getX() - currentPosition.getX()));
  Angle orientationDifference = targetOrientation - currentOrientation;

  double inputRotation = orientationDifference.getValueBetweenMinusPiAndPi();
  double inputTranslation = target.distanceTo(currentPosition);

  rotationSpeed = m_rotationController->evaluate(inputRotation);

  translationSpeed = m_translationController->evaluate(inputTranslation);
}

void RobotDriveControl::reset(const Pose &/*start*/)
{
  m_translationController->resetTo(0);
  m_rotationController->resetTo(0);
}
