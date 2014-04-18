#ifndef ROBOSOCCER_COMMON_TIME_STOPWATCH_H
#define ROBOSOCCER_COMMON_TIME_STOPWATCH_H

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
class Watch;

class StopWatch
{
public:
	StopWatch(const Watch &watch);

	double getTimeAndRestart();
	double getTime() const;

private:
	const Watch &m_watch;
	double m_startTime;
};
}
}
}

#endif


