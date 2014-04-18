#ifndef ROBOSOCCER_COMMON_ROUTING_ROUTINGRESULT_H
#define ROBOSOCCER_COMMON_ROUTING_ROUTINGRESULT_H

#include <list>
#include "common/routing/routingobstacle.h"
#include "common/routing/route.h"

namespace RoboSoccer
{
namespace Common
{
namespace Routing
{
class RoutingResult
{
public:
	RoutingResult();
	RoutingResult(const Route &route, const std::list<RoutingObstacle> &obstacles);

	bool isValid() const;
	const Route& getRoute() const;
	const std::list<RoutingObstacle>& getObstacles() const;

private:
	Route m_route;
	std::list<RoutingObstacle> m_obstacles;

};
}
}
}

#endif


