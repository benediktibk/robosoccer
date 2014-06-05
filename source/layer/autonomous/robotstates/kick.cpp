#include "layer/autonomous/robotstates/kick.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/time/stopwatch.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

Kick::Kick(
		Abstraction::ControllableRobot &robot, IntelligentBall const &ball,
		Watch const &watch, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_stopWatch(new StopWatch(watch)),
	m_ball(ball),
	m_alreadyKicked(false),
	m_stopWatchRestarted(false)
{ }

Kick::~Kick()
{
	delete m_stopWatch;
	m_stopWatch = 0;
}

bool Kick::reachedTarget() const
{
	return false;
}

bool Kick::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}

bool Kick::isEquivalentToDriveToDirect(const Pose &) const
{
	return false;
}

RobotState *Kick::nextState(bool)
{
	if (!m_stopWatchRestarted)
	{
		m_stopWatchRestarted = true;
		m_stopWatch->getTimeAndRestart();
	}

	if (getRobot().isMoving() || !m_alreadyKicked)
		return 0;
	else
		return new ReachedTarget(getRobot(), getLogger(), getLogFileType());
}

void Kick::update()
{
	if (m_alreadyKicked)
		return;

	getRobot().kick(m_ball.getPosition());
	m_alreadyKicked = true;
	m_stopWatch->getTimeAndRestart();
}

string Kick::getName() const
{
	return string("kick");
}
