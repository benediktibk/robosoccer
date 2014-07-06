#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAM_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAM_H

#include <vector>
#include "layer/autonomous/obstaclesource.h"

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

	class EnemyTeam :
			public ObstacleSource
	{
	public:
		virtual ~EnemyTeam() { }

		virtual const Abstraction::ReadableRobot& getPlayerNextToBall(const IntelligentBall &ball) = 0;
		virtual std::vector<Common::Geometry::Circle> getObstacles() const = 0;
		virtual void updateSensors() = 0;
	};
}
}
}
#endif
