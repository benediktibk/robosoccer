#include "layer/abstraction/robotturncontrol.h"
#include "common/other/pidcontroller.h"
#include "common/geometry/angle.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Other;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Geometry;

RobotTurnControl::RobotTurnControl(const Watch &watch) :
	m_controller(new PIDController(0.25, 0.05, 0, watch))
{ }

RobotTurnControl::~RobotTurnControl()
{
	delete m_controller;
	m_controller = 0;
}

double RobotTurnControl::evaluate(const Angle &currentOrientation, const Angle &targetOrientation)
{
	Angle orientationDifference = targetOrientation - currentOrientation;
	double inputValue = orientationDifference.getValueBetweenMinusPiAndPi();
	return m_controller->evaluate(inputValue);
}

void RobotTurnControl::reset()
{
	m_controller->resetTo(0);
}
