#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/autonomous/robotstatedriveto.h"
#include "layer/autonomous/robotstatekick.h"
#include "layer/autonomous/robotstateturnto.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/pose.h"
#include "common/logging/logger.h"
#include "common/geometry/circle.h"
#include <sstream>

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Logging;

RobotImpl::RobotImpl(ControllableRobot &robot, const Watch &watch, Logger &logger) :
	m_robot(robot),
	m_watch(watch),
	m_logger(logger),
	m_currentState(new RobotStateReachedTarget(robot))
{ }

RobotImpl::~RobotImpl()
{
	delete m_currentState;
	m_currentState = 0;
}

void RobotImpl::goTo(const Point &position)
{
	//! @todo should consider obstacles

	if (m_currentState->isEquivalentToDriveTo(Point(position)))
		return;

	switchIntoState(new RobotStateDriveTo(m_robot, position));
}

Pose RobotImpl::getCurrentPose() const
{
	return m_robot.getPose();
}

Circle RobotImpl::getObstacle() const
{
	return m_robot.createObstacle();
}

bool RobotImpl::targetReached() const
{
	return false;
}

bool RobotImpl::cantReachTarget() const
{
	return m_currentState->cantReachTarget();
}

void RobotImpl::kick(unsigned int force, IntelligentBall const &ball)
{
	Point ballPosition = ball.getPosition();
	Pose ownPose = getCurrentPose();
	Point const &ownPosition = ownPose.getPosition();
	double distanceToBall = ownPosition.distanceTo(ballPosition);

	//! there is a maximum distance to the ball specified in the documentation
	if (distanceToBall >= 0.25)
	{
		m_logger.logErrorToConsoleAndWriteToGlobalLogFile("distance to ball is too big, can not kick it");
		//! replace with cant reach target
		switchIntoState(new RobotStateReachedTarget(m_robot));
	}
	else
		switchIntoState(new RobotStateTurnTo(m_robot, ballPosition, new RobotStateKick(m_robot, force, m_watch)));
}

void RobotImpl::update()
{
	m_currentState->update();
}

void RobotImpl::switchIntoState(RobotState *state)
{
	stringstream stream;
	stream << "switching into " << state->getName();
	m_logger.logToLogFileOfType(Logger::LogFileTypeRobot, stream.str());
	delete m_currentState;
	m_currentState = state;
}

void RobotImpl::stop()
{
	switchIntoState(new RobotStateReachedTarget(m_robot));
}
