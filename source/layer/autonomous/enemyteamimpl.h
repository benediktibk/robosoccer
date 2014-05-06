#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAMIMPL_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAMIMPL_H

#include <vector>
#include "layer/autonomous/enemyteam.h"

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
	class EnemyTeamImpl
			: public EnemyTeam
	{
	public:
		EnemyTeamImpl(Abstraction::Storage &storage);
		virtual ~EnemyTeamImpl();
		virtual const Abstraction::ReadableRobot& getGoalkeeper();
		virtual const Abstraction::ReadableRobot& getPlayerNextToBall(const IntelligentBall &ball);
		virtual void getObstacles();

	private:
		std::vector<const Abstraction::ReadableRobot*> m_robots;
	};
}
}
}

#endif
