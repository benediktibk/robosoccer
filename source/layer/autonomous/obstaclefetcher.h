#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHER_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHER_H

#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Circle;
}
}
namespace Layer
{
namespace Autonomous
{
	class IntelligentBall;
	class Team;
	class EnemyTeam;

	class ObstacleFetcher
	{
	public:
		ObstacleFetcher(std::vector<Common::Geometry::Circle> &obstaclesTeam,
						std::vector<Common::Geometry::Circle> const &obstaclesEnemyTeam,
						Common::Geometry::Circle &obstacleBall);

		const std::vector<Common::Geometry::Circle> getAllObstacles() const;

	private:
		std::vector<Common::Geometry::Circle> m_obstacles;
	};
}
}
}

#endif // ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHER_H


