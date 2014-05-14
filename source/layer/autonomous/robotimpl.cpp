#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/autonomous/robotstatedriveto.h"
#include "layer/autonomous/robotstatedrivetodirect.h"
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

RobotImpl::RobotImpl(ControllableRobot &robot, const Common::Routing::Router &router, const Watch &watch, Logger &logger) :
	m_robot(robot),
	m_router(router),
	m_watch(watch),
	m_logger(logger),
	m_currentRoute(0),
	m_currentState(new RobotStateReachedTarget(robot))
{ }

RobotImpl::~RobotImpl()
{
	delete m_currentState;
	m_currentState = 0;
}

void RobotImpl::goTo(const Pose &position)
{
	if (m_currentState->isEquivalentToDriveTo(position))
		return;

	switchIntoState(new RobotStateDriveTo(m_robot, position, m_watch));
}

Pose RobotImpl::getCurrentPose() const
{
	return m_robot.getPose();
}

Circle RobotImpl::getObstacle() const
{
	return m_robot.getObstacle();
}

bool RobotImpl::targetReached() const
{
	return m_currentState->reachedTarget();
}

bool RobotImpl::cantReachTarget() const
{
	return m_currentState->cantReachTarget();
}

void RobotImpl::kick(unsigned int force, IntelligentBall const &ball)
{
	Point ballPosition = ball.getPosition();
	switchIntoState(new RobotStateTurnTo(m_robot, ballPosition, m_watch, new RobotStateKick(m_robot, force, m_watch)));
}

void RobotImpl::update()
{
	RobotState *nextState = m_currentState->nextState();

	if (nextState != 0)
		switchIntoState(nextState);

	m_currentState->update();
	m_robot.update();
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

void RobotImpl::goToDirect(const Pose &position)
{
	if (m_currentState->isEquivalentToDriveToDirect(position))
		return;

	switchIntoState(new RobotStateDriveToDirect(m_robot, position, m_watch));
}
