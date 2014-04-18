#ifndef ROBOSOCCER_COMMON_TIME_WATCHIMPL_H
#define ROBOSOCCER_COMMON_TIME_WATCHIMPL_H

#include "common/time/watch.h"

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
class WatchImpl :
		public Watch
{
public:
	WatchImpl();

	virtual double getTime() const;

private:
	double getCurrentAbsoluteTime() const;

private:
	double m_initialTime;
};
}
}
}

#endif
