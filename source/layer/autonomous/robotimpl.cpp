#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/autonomous/robotstates/drivetoinitialrotation.h"
#include "layer/autonomous/robotstates/drivetodirectinitialrotation.h"
#include "layer/autonomous/robotstates/kick.h"
#include "layer/autonomous/robotstates/turnto.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/pose.h"
#include "common/logging/logger.h"
#include "common/geometry/circle.h"
#include <sstream>
#include <assert.h>

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Logging;

RobotImpl::RobotImpl(ControllableRobot &robot, const Common::Routing::Router &router,
		const Watch &watch, Logger &logger, unsigned int robotIndex, ObstacleFetcher &obstacleFetcher) :
	m_robot(robot),
	m_router(router),
	m_watch(watch),
	m_logger(logger),
	m_currentState(0),
	m_logFileType(Logger::LogFileTypeInvalid),
	m_obstacleFetcher(obstacleFetcher),
	m_lastMovementState(false),
	m_currentMovementState(false),
	m_movementStopped(false)
{
	switch(robotIndex)
	{
	case 0:
		m_logFileType = Logger::LogFileTypeAutonomousRobotGoalie;
		log("logging autonomous goalie");
		break;
	case 1:
		m_logFileType = Logger::LogFileTypeAutonomousRobotOne;
		log("logging autonomous robot one");
		break;
	case 2:
		m_logFileType = Logger::LogFileTypeAutonomousRobotTwo;
		log("logging autonomous robot two");
		break;
	default:
		assert(false);
		break;
	}

	m_currentState = new ReachedTarget(robot, logger, m_logFileType);
}

RobotImpl::~RobotImpl()
{
	delete m_currentState;
	m_currentState = 0;
}

void RobotImpl::goTo(const Pose &position, bool ignoreBall, bool driveSlowlyAtTheEnd, bool ignoreGoalObstacles)
{
	if (m_currentState->isEquivalentToDriveTo(position))
	{
		log("new target for go to is equal to the current one");
		return;
	}

	switchIntoState(new DriveToInitialRotation(
						m_robot, position, m_router, m_logger, m_logFileType,
						m_obstacleFetcher, *this, ignoreBall, driveSlowlyAtTheEnd, ignoreGoalObstacles));
	logPosition("target is", position);
}

Pose RobotImpl::getCurrentPose() const
{
	return m_robot.getPose();
}

Circle RobotImpl::getObstacle() const
{
	return m_robot.getObstacle();
}

vector<Circle> RobotImpl::getObstacles() const
{
	vector<Circle> result;
	result.push_back(getObstacle());
	return result;
}

bool RobotImpl::reachedTarget() const
{
	return m_currentState->reachedTarget();
}

void RobotImpl::kick(IntelligentBall const &ball)
{
	Point ballPosition = ball.getPosition();
	switchIntoState(new TurnTo(m_robot, ballPosition, new Kick(m_robot, ball, m_watch, m_logger, m_logFileType), m_logger, m_logFileType));
}

void RobotImpl::update()
{
	updateMovementStopped();
	bool stateChanged;
	bool movementStopped = m_movementStopped;

	do
	{
		RobotState *nextState = m_currentState->nextState(movementStopped);
		stateChanged = nextState != 0;

		if (stateChanged)
			switchIntoState(nextState);

		movementStopped = false;
	} while(stateChanged);

	m_currentState->update(movementStopped);
	m_robot.update();
}

const RobotState &RobotImpl::getCurrentState() const
{
	return *m_currentState;
}


void RobotImpl::switchIntoState(RobotState *state)
{
	log(string("switching into ") + state->getName());
	delete m_currentState;
	m_currentState = state;
}

void RobotImpl::stop()
{
	switchIntoState(new ReachedTarget(m_robot, m_logger, m_logFileType));
}

void RobotImpl::goToDirect(const Pose &position)
{
	if (m_currentState->isEquivalentToDriveToDirect(position))
	{
		log("new target for go to direct is equal to the current one");
		return;
	}

	switchIntoState(new DriveToDirectInitialRotation(m_robot, position, m_logger, m_logFileType));
	logPosition("target is", position);
}

void RobotImpl::log(const string &message)
{
	m_logger.logToLogFileOfType(m_logFileType, message);
}

void RobotImpl::logPosition(const string &message, const Point &position)
{
	stringstream stream;
	stream << message << ": " << position;
	log(stream.str());
}

void RobotImpl::updateMovementStopped()
{
	m_lastMovementState = m_currentMovementState;
	m_currentMovementState = m_robot.isMoving();

	if (m_lastMovementState && !m_currentMovementState)
	{
		m_movementStopped = true;
		log("movement stopped");
	}
	else if (m_currentMovementState)
	{
		if (m_movementStopped)
			log("movement not stopped anymore");
		m_movementStopped = false;
	}
}
