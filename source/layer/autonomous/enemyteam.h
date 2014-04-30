#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAM_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAM_H

namespace RoboSoccer
{
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

		virtual const Abstraction::ReadableRobot& getGoalkeeper() = 0;
		virtual const Abstraction::ReadableRobot& getPlayerNextToBall(const IntelligentBall &ball) = 0;
		virtual void getObstacles() = 0;

	};
}
}
}
#endif
