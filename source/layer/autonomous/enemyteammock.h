#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAMMOCK_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAMMOCK_H

#include "layer/autonomous/enemyteam.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class EnemyTeamMock :
			public EnemyTeam
	{
	public:
		EnemyTeamMock();
		virtual ~EnemyTeamMock();

	};
}
}
}

#endif


