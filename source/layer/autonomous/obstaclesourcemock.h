#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLESOURCEMOCK_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLESOURCEMOCK_H

#include "layer/autonomous/obstaclesource.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class ObstacleSourceMock :
			public ObstacleSource
	{
	public:
		virtual std::vector<Common::Geometry::Circle> getObstacles() const;

		void setObstacles(std::vector<Common::Geometry::Circle> const &obstacles);

	private:
		std::vector<Common::Geometry::Circle> m_obstacles;
	};
}
}
}

#endif