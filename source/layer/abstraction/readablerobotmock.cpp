#include "layer/abstraction/readablerobotmock.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

Pose ReadableRobotMock::getPose() const
{
	return m_pose;
}

Circle ReadableRobotMock::getObstacle() const
{
	return Circle(m_pose.getPosition(),0.095);
}

void ReadableRobotMock::setPose(const Pose &pose)
{
	m_pose = pose;
}

void ReadableRobotMock::updateSensors()
{ }
