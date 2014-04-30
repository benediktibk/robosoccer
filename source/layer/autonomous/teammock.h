#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TEAMMOCK_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TEAMMOCK_H

#include "layer/autonomous/team.h"
#include "layer/autonomous/robotmock.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class TeamMock :
			public Team
	{
	public:
		TeamMock();
		virtual ~TeamMock();

		virtual Robot& getGoalie();
		virtual Robot& getPlayerCloserToBall(const IntelligentBall &ball);
		virtual Robot& getPlayerFartherAwayFromBall(const IntelligentBall &ball);
		virtual Robot& getFirstFieldPlayer();
		virtual Robot& getSecondFieldPlayer();
		virtual Robot& getRobotByNumber(unsigned int i);

	private:
		RobotMock m_robot;
	};
}
}
}

#endif


