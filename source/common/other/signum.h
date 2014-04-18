#ifndef ROBOSOCCER_COMMON_OTHER_SIGNUM_H
#define ROBOSOCCER_COMMON_OTHER_SIGNUM_H

namespace RoboSoccer
{
namespace Common
{
namespace Other
{
template <typename T> int sgn(T val)
{
	return (T(0) < val) - (val < T(0));
}
}
}
}

#endif
