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
namespace Common
{
namespace Logging
{
	class Logger;
}
namespace Time
{
	class Watch;
}
}
namespace Layer
{
namespace Abstraction
{
	class StorageImpl :
			public Storage
	{
	public:
		StorageImpl(int clientNumber, TeamColor teamColor, Common::Logging::Logger &logger, Common::Time::Watch const &watch);
		virtual ~StorageImpl();

		virtual Ball& getBall();
		virtual ReadableRobot & getEnemyRobot(unsigned int number);
		virtual ControllableRobot& getOwnRobot(unsigned int number);
		virtual RefereeBase& getReferee();

	private:
		KogniMobil::RTDBConn *m_dataBase;
		std::vector<ReadableRobot*> m_enemyRobots;
		std::vector<ControllableRobot*> m_ownRobots;
		Ball *m_ball;
		RefereeBase *m_referee;
	};
}
}
}

#endif


