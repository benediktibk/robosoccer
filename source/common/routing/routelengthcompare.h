#ifndef ROBOSOCCER_COMMON_ROUTING_ROUTELENGTHCOMPARE_H
#define ROBOSOCCER_COMMON_ROUTING_ROUTELENGTHCOMPARE_H

namespace RoboSoccer
{
namespace Common
{
namespace Routing
{
	class Route;

	class RouteLengthCompare
	{
	public:
		RouteLengthCompare();

		bool operator() (const Route &one, const Route &two) const;
	};
}
}
}

#endif


