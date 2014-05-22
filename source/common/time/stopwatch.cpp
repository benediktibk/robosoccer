#include "common/time/stopwatch.h"
#include "common/time/watch.h"

using namespace RoboSoccer::Common::Time;

StopWatch::StopWatch(const Watch &watch) :
	m_watch(watch),
	m_startTime(watch.getTime())
{ }

double StopWatch::getTimeAndRestart()
{
	double time = m_watch.getTime();
	double timeDifference = time - m_startTime;
	m_startTime = time;
	return timeDifference;
}

double StopWatch::getTime() const
{
	double time = m_watch.getTime();
	return time - m_startTime;
}

void StopWatch::restart()
{
	m_startTime = m_watch.getTime();
}

void StopWatch::restart(double startTime)
{
	m_startTime = m_watch.getTime() - startTime;
}
