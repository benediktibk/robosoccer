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
		ObstacleFetcher(Team &team, EnemyTeam const& enemyTeam, IntelligentBall &ball);

		const std::vector<Common::Geometry::Circle> getAllObstacles() const;

	private:
		Team &m_team;
		EnemyTeam const& m_enemyTeam;
		IntelligentBall &m_ball;
	};
}
}
}

#endif // ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHER_H


