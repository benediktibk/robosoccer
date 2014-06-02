#include "layer/autonomous/robotstatekick.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/time/stopwatch.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotStateKick::RobotStateKick(
		Abstraction::ControllableRobot &robot, IntelligentBall const &ball,
		Watch const &watch, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_stopWatch(new StopWatch(watch)),
	m_ball(ball),
	m_alreadyKicked(false),
	m_stopWatchRestarted(false)
{ }

RobotStateKick::~RobotStateKick()
{
	delete m_stopWatch;
	m_stopWatch = 0;
}

bool RobotStateKick::reachedTarget() const
{
	return false;
}

bool RobotStateKick::cantReachTarget() const
{
	return false;
}

bool RobotStateKick::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}

bool RobotStateKick::isEquivalentToDriveToDirect(const Pose &) const
{
	return false;
}

RobotState *RobotStateKick::nextState()
{
	if (!m_stopWatchRestarted)
	{
		m_stopWatchRestarted = true;
		m_stopWatch->getTimeAndRestart();
	}

	if (getRobot().isMoving())
		return 0;
	else
		return new RobotStateReachedTarget(getRobot(), getLogger(), getLogFileType());
}

void RobotStateKick::updateInternal()
{
	if (m_alreadyKicked)
		return;

	getRobot().kick(m_ball.getPosition());
	m_alreadyKicked = true;
	m_stopWatch->getTimeAndRestart();
}

string RobotStateKick::getName() const
{
	return string("kick");
}
