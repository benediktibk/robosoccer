#include "layer/autonomous/robotstatekick.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/time/stopwatch.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Geometry;

RobotStateKick::RobotStateKick(Abstraction::ControllableRobot &robot, unsigned int force, Watch const &watch) :
	RobotState(robot),
	m_stopWatch(new StopWatch(watch)),
	m_force(force),
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

RobotState *RobotStateKick::nextState()
{
	if (!m_stopWatchRestarted)
	{
		m_stopWatchRestarted = true;
		m_stopWatch->getTimeAndRestart();
	}

	if (m_stopWatch->getTime() < 0.5)
		return 0;

	return new RobotStateReachedTarget(getRobot());
}

void RobotStateKick::updateInternal()
{
	if (m_alreadyKicked)
		return;

	getRobot().kick(m_force);
	m_alreadyKicked = true;
	m_stopWatch->getTimeAndRestart();
}

string RobotStateKick::getName() const
{
	return string("kick");
}
