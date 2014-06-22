#ifndef ROBOSOCCER_LAYER_MAIN_APPLICATION_H
#define ROBOSOCCER_LAYER_MAIN_APPLICATION_H

#include "layer/abstraction/teamcolor.h"

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
namespace Geometry
{
	class Angle;
}
}
namespace Layer
{
namespace Abstraction
{
	class Storage;
	class FieldPositionCheckerGoalkeeper;
	class FieldPositionCheckerFieldPlayer;
}
namespace Autonomous
{
	class EnemyTeamImpl;
	class TeamImpl;
	class IntelligentBall;
	class TargetPositionFetcher;
	class ObstacleFetcher;
}
namespace Main
{
	class RouteInformationServer;

	class Application
	{
	public:
		Application(Abstraction::TeamColor ownTeamColor, int ownClientNumber, bool enableHardwareCheck);
		~Application();

		void run();
		void stop();

	private:
		bool checkHardware();
		void turnAllRobotsTo(Common::Geometry::Angle const &angle);

	private:
		Common::Logging::Logger *m_logger;
		Common::Time::Watch *m_watch;
		Abstraction::Storage *m_storage;
		Abstraction::FieldPositionCheckerGoalkeeper *m_fieldPositionCheckerGoalKeeper;
		Abstraction::FieldPositionCheckerFieldPlayer *m_fieldPositionCheckerFieldPlayer;
		Autonomous::ObstacleFetcher *m_obstacleFetcher;
		Autonomous::EnemyTeamImpl *m_enemyTeam;
		Autonomous::TeamImpl *m_ownTeam;
		Autonomous::IntelligentBall *m_ball;
		Autonomous::TargetPositionFetcher *m_targetPositionFetcher;
		RouteInformationServer *m_routeInformationServer;
		bool m_stop;
		bool m_enableHardwareCheck;
	};
}
}
}

#endif


