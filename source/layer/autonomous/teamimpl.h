#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TEAMIMPL_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TEAMIMPL_H

#include "layer/autonomous/team.h"

namespace RoboSoccer
{
namespace Common
{
namespace Routing
{
	class Router;
}
}
namespace Layer
{
namespace Abstraction
{
	class Storage;
}
namespace Main
{
	class FieldPositionCheckerGoalkeeper;
	class FieldPositionCheckerFieldPlayer;
}
namespace Autonomous
{
	class IntelligentBall;
	class Robot;

	class TeamImpl :
			public Team
	{
	public:
		TeamImpl(Abstraction::Storage &storage, const Common::Time::Watch &watch,
				 Common::Logging::Logger &logger, Main::FieldPositionCheckerGoalkeeper &fieldPositionCheckerGoalkeeper,
				 Main::FieldPositionCheckerFieldPlayer &fieldPositionCheckerFieldPlayer);
		virtual ~TeamImpl();

		virtual Robot& getGoalie();
		virtual Robot& getPlayerCloserToBall(const IntelligentBall &ball);
		virtual Robot& getPlayerFartherAwayFromBall(const IntelligentBall &ball);
		virtual Robot& getFirstFieldPlayer();
		virtual Robot& getSecondFieldPlayer();
		virtual Robot& getRobotByNumber(unsigned int i);
		virtual Robot const& getRobotByNumber(unsigned int i) const;
		virtual std::vector<Common::Geometry::Circle> getObstacles();

	private:
		Common::Routing::Router const *m_routerGoalie;
		Common::Routing::Router const *m_routerFieldPlayer;
		Robot *m_goalie;
		Robot *m_fieldPlayerOne;
		Robot *m_fieldPlayerTwo;
	};
}
}
}

#endif
