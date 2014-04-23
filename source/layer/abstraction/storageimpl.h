#ifndef ROBOSOCCER_LAYER_ABSTRACTION_STORAGEIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_STORAGEIMPL_H

#include "layer/abstraction/storage.h"
#include "layer/abstraction/teamcolor.h"
#include <vector>

namespace KogniMobil
{
	class RTDBConn;
}

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class StorageImpl :
			public Storage
	{
	public:
		StorageImpl(int clientNumber, TeamColor teamColor);
		virtual ~StorageImpl();

		virtual Ball& getBall();
		virtual ReadableRobot& getEnemyRobot(unsigned int number);
		virtual ControllableRobot& getOwnRobot(unsigned int number);
		virtual Referee& getReferee();

	private:
		KogniMobil::RTDBConn *m_dataBase;
		std::vector<ReadableRobot*> m_enemyRobots;
		std::vector<ControllableRobot*> m_ownRobots;
		Ball *m_ball;
		Referee *m_referee;
	};
}
}
}

#endif


