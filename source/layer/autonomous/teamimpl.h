#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TEAMIMPL_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TEAMIMPL_H

#include "layer/autonomous/team.h"
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

	class TeamImpl :
			public Team
	{
	public:
		TeamImpl(Abstraction::Storage &storage);
		virtual ~TeamImpl();

		virtual Robot& getGoalie();
		virtual Robot& getPlayerCloserToBall(const IntelligentBall &ball);
		virtual Robot& getPlayerFartherAwayFromBall(const IntelligentBall &ball);
		virtual Robot& getFirstFieldPlayer();
		virtual Robot& getSecondFieldPlayer();
		virtual Robot& getRobotByNumber(unsigned int i);

	private:
		Robot *m_goalie;
		Robot *m_fieldPlayerOne;
		Robot *m_fieldPlayerTwo;
	};
}
}
}

#endif
