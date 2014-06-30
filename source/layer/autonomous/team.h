#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TEAM_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TEAM_H

#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
	class Watch;
}
namespace Logging
{
	class Logger;
}
namespace Geometry
{
	class Point;
	class Pose;
	class Circle;
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
		virtual void updateSensors() = 0;
		virtual void updateActuators() = 0;
	};
}
}
}
#endif
