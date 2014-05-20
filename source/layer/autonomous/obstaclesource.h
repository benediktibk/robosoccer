#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLESOURCE_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLESOURCE_H

#include <vector>
#include "common/geometry/circle.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class ObstacleSource
	{
	public:
		virtual ~ObstacleSource() { }

		virtual std::vector<Common::Geometry::Circle> getObstacles() const = 0;
	};
}
}
}

#endif