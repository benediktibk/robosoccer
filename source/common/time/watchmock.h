#ifndef ROBOSOCCER_COMMON_TIME_WATCHMOCK_H
#define ROBOSOCCER_COMMON_TIME_WATCHMOCK_H

#include "common/time/watch.h"

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
class WatchMock :
		public Watch
{
public:
	WatchMock();

	virtual double getTime() const;

	void setTime(double time);

private:
	double m_time;
};
}
}
}

#endif


