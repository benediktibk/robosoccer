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
	class ObstacleSource;

	class ObstacleFetcher
	{
	public:
		ObstacleFetcher(Team const &team,
						EnemyTeam const &enemyTeam,
						IntelligentBall const &obstacleBall);
		~ObstacleFetcher();

		const std::vector<Common::Geometry::Circle> getAllObstacles() const;

	private:
		std::vector<ObstacleSource const *> m_sources;
	};
}
}
}

#endif