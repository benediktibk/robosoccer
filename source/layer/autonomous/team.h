#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TEAM_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TEAM_H

#include "layer/autonomous/robot.h"

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
}
namespace Layer
{
namespace Abstraction
{
	class Storage;
}
namespace Autonomous
{
	class IntelligentBall;

	class Team
	{
	public:
		Team(Abstraction::Storage &storage, Common::Time::Watch const &watch, Common::Logging::Logger &logger);

		Robot& getGoalie();
		Robot& getPlayerCloserToBall(const IntelligentBall &ball);
		Robot& getPlayerFartherAwayFromBall(const IntelligentBall &ball);
		Robot& getFirstFieldPlayer();
		Robot& getSecondFieldPlayer();
		Robot& getRobotByNumber(unsigned int i);

	private:
		Robot *m_goalie;
		Robot *m_fieldPlayerOne;
		Robot *m_fieldPlayerTwo;
	};
}
}
}

#endif