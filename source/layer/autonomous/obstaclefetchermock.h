#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHERMOCK_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHERMOCK_H

#include "layer/autonomous/obstaclefetcher.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class ObstacleFetcherMock :
			public ObstacleFetcher
	{
	public:
		ObstacleFetcherMock();

		virtual std::vector<Common::Geometry::Circle> getAllObstacles() const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMe(ObstacleSource const &me) const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeInRange(
				ObstacleSource const &me, Common::Geometry::Point const &ownPosition, double distance) const;

		void setAllObstacles(std::vector<Common::Geometry::Circle> const &obstacles);
		void setAllObstaclesButMe(std::vector<Common::Geometry::Circle> const &obstacles);
		void setAllObstaclesButMeInRange(std::vector<Common::Geometry::Circle> const &obstacles);

	private:
		std::vector<Common::Geometry::Circle> m_allObstacles;
		std::vector<Common::Geometry::Circle> m_allObstaclesButMe;
		std::vector<Common::Geometry::Circle> m_allObstaclesButMeInRange;
	};
}
}
}

#endif
