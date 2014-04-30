#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TEAM_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TEAM_H

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;
	class Pose;
}
}
namespace Layer
{
namespace Autonomous
{
	class IntelligentBall;
	class Robot;

	class Team
	{
	public:
		virtual ~Team() { }

		virtual Robot& getGoalie() = 0;
		virtual Robot& getPlayerCloserToBall(const IntelligentBall &ball) = 0;
		virtual Robot& getPlayerFartherAwayFromBall(const IntelligentBall &ball) = 0;
		virtual Robot& getFirstFieldPlayer() = 0;
		virtual Robot& getSecondFieldPlayer() = 0;
		virtual Robot& getRobotByNumber(unsigned int i) = 0;
	};
}
}
}
#endif
