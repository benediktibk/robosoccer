#ifndef ROBOSOCCER_COMMON_TIME_WATCH_H
#define ROBOSOCCER_COMMON_TIME_WATCH_H

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
	class Watch
	{
	public:
		virtual ~Watch() { }

		virtual double getTime() const = 0;
	};
}
}
}

#endif
