#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAM_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAM_H

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
namespace Abstraction
{
	class ReadableRobot;
}
namespace Autonomous
{
	class IntelligentBall;

	class EnemyTeam
	{
	public:
		virtual ~EnemyTeam() { }

		virtual const Abstraction::ReadableRobot& getPlayerNextToBall(const IntelligentBall &ball) = 0;
		virtual const std::vector<Common::Geometry::Circle> getObstacles() = 0;

	};
}
}
}
#endif
