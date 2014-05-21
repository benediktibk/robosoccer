#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAMMOCK_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAMMOCK_H

#include "layer/autonomous/enemyteam.h"
#include <vector>

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class ReadableRobotMock;
}
namespace Autonomous
{
	class EnemyTeamMock :
			public EnemyTeam
	{
	public:
		EnemyTeamMock();
		virtual ~EnemyTeamMock();

		virtual const Abstraction::ReadableRobot& getPlayerNextToBall(const IntelligentBall &ball);
		virtual std::vector<Common::Geometry::Circle> getObstacles() const;

		void setObstacles(std::vector<Common::Geometry::Circle> const &obstacles);

	private:
		std::vector<Abstraction::ReadableRobotMock*> m_robots;
		std::vector<Common::Geometry::Circle> m_obstacles;


	};
}
}
}

#endif


