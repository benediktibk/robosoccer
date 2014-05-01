#ifndef ROBOSOCCER_LAYER_ABSTRACTION_STORAGEMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_STORAGEMOCK_H

#include "layer/abstraction/storage.h"
#include "layer/abstraction/ballmock.h"
#include "layer/abstraction/refereemock.h"
#include "layer/abstraction/readablerobotmock.h"
#include "layer/abstraction/controllablerobotmock.h"
#include <vector>

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class StorageMock :
			public Storage
	{
	public:
		virtual Ball const& getBall() const;
		virtual ReadableRobot  const& getEnemyRobot(unsigned int number) const;
		virtual ControllableRobot& getOwnRobot(unsigned int number);
		virtual RefereeBase& getReferee();

		void addControllableRobot(ControllableRobotMock ownRobot);

	private:
		BallMock m_ball;
		RefereeMock m_referee;
		std::vector<ReadableRobotMock> m_enemyRobot;
		std::vector<ControllableRobotMock> m_ownRobot;
	};
}
}
}

#endif


