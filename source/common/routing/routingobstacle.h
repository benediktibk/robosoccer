#ifndef ROBOSOCCER_COMMON_ROUTING_ROUTINGOBSTACLE_H
#define ROBOSOCCER_COMMON_ROUTING_ROUTINGOBSTACLE_H

#include "common/geometry/circle.h"

namespace RoboSoccer
{
namespace Common
{
namespace Routing
{
class RoutingObstacle
{
public:
	RoutingObstacle();
	RoutingObstacle(const Geometry::Circle &obstacle, bool wentRightBeside);

	bool isValid() const;
	bool wentRightBeside() const;
	const Geometry::Circle& getObstacle() const;

	bool operator==(const RoutingObstacle &routingObstacle) const;

private:
	Geometry::Circle m_obstacle;
	bool m_wentRightBeside;
	bool m_valid;
};
}
}
}

#endif


