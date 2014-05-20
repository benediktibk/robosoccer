#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHERIMPL_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHERIMPL_H

#include "layer/autonomous/obstaclefetcher.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class IntelligentBall;
	class Team;
	class EnemyTeam;

	class ObstacleFetcherImpl :
			public ObstacleFetcher
	{
	public:
		ObstacleFetcherImpl();
		~ObstacleFetcherImpl();

		virtual std::vector<Common::Geometry::Circle> getAllObstacles() const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMe(ObstacleSource const &me) const;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeInRange(
				ObstacleSource const &me, Common::Geometry::Point const &ownPosition, double distance) const;

	private:
		std::vector<ObstacleSource const *> m_sources;
	};
}
}
}

#endif


