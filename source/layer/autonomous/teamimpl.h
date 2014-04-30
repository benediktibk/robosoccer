#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TEAMIMPL_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TEAMIMPL_H

#include "layer/autonomous/robot.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class Storage;
}
namespace Autonomous
{
	class IntelligentBall;

	class TeamImpl
	{
	public:
		TeamImpl(Abstraction::Storage &storage);
		~TeamImpl();

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
