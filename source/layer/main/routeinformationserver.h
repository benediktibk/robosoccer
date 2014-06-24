#ifndef ROBOSOCCER_LAYER_MAIN_ROUTEINFORMATIONSERVER_H
#define ROBOSOCCER_LAYER_MAIN_ROUTEINFORMATIONSERVER_H

#include <vector>
#include <string>

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
	class Logger;
}
}
namespace Layer
{
namespace Abstraction
{
	class TCPServerSocket;
}
namespace Autonomous
{
	class ObstacleFetcher;
	class ObstacleSource;
	class Robot;
}
namespace Main
{
	class RouteInformationServer
	{
	public:
		RouteInformationServer(Abstraction::TCPServerSocket &socket);

		void updateClients(
				Autonomous::ObstacleFetcher const &obstacleFetcher,
				Autonomous::Robot const &robotOne,
				Autonomous::Robot const &robotTwo,
				Autonomous::ObstacleSource const &goalkeeper);

	private:
		void sendObstacles(Autonomous::ObstacleFetcher const &obstacleFetcher, const Autonomous::ObstacleSource &goalkeeper);
		void sendRoute(std::string const &name, Autonomous::Robot const &robot);

	private:
		Abstraction::TCPServerSocket &m_socket;
	};
}
}
}

#endif
