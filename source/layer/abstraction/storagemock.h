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
		StorageMock();
		virtual ~StorageMock();

		virtual Ball &getBall();
		virtual ReadableRobot & getEnemyRobot(unsigned int number);
		virtual ControllableRobot& getOwnRobot(unsigned int number);
		virtual RefereeBase& getReferee();

		ControllableRobotMock& getOwnRobotMock(unsigned int number);
		ReadableRobotMock& getEnemyRobotMock(unsigned int number);

	private:
		BallMock m_ball;
		RefereeMock m_referee;
		std::vector<ReadableRobotMock*> m_enemyRobot;
		std::vector<ControllableRobotMock*> m_ownRobot;
	};
}
}
}

#endif


