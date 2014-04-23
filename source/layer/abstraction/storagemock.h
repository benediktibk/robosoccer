#ifndef ROBOSOCCER_LAYER_ABSTRACTION_STORAGEMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_STORAGEMOCK_H

#include "layer/abstraction/storage.h"
#include "layer/abstraction/ballmock.h"
#include "layer/abstraction/refereemock.h"
#include "layer/abstraction/readablerobotmock.h"
#include "layer/abstraction/controllablerobotmock.h"

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
		virtual Referee& getReferee();

	private:
		BallMock m_ball;
		RefereeMock m_referee;
		ReadableRobotMock m_enemyRobot;
		ControllableRobotMock m_ownRobot;
	};
}
}
}

#endif


