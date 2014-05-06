#include "layer/abstraction/robotdrivecontrol.h"
#include "common/other/pidcontroller.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Other;
using namespace RoboSoccer::Common::Geometry;

RobotDriveControl::RobotDriveControl(const Watch &watch) :
	m_rotationController(new PIDController(1, 0, 0, watch)),
	m_translationController(new PIDController(1, 0, 0, watch))
{ }

RobotDriveControl::~RobotDriveControl()
{
	delete m_rotationController;
	m_rotationController = 0;
	delete m_translationController;
	m_translationController = 0;
}

void RobotDriveControl::evaluate(const Pose &/*current*/, const Pose &/*target*/, double &translationSpeed, double &rotationSpeed)
{
	translationSpeed = 0;
	rotationSpeed = 0;
}

void RobotDriveControl::reset(const Pose &/*start*/)
{
	m_translationController->resetTo(0);
	m_rotationController->resetTo(0);
}
