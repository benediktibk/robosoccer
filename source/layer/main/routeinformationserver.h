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
namespace Autonomous
{
	class ObstacleFetcher;
	class Robot;
}
namespace Main
{
	class RouteInformationServer
	{
	public:
		RouteInformationServer(Common::Logging::Logger &logger, unsigned int port);
		~RouteInformationServer();

		bool isValid() const;
		void updateClients(
				Autonomous::ObstacleFetcher const &obstacleFetcher,
				Autonomous::Robot const &robotOne,
				Autonomous::Robot const &robotTwo);

	private:
		void acceptNewClients();
		void updateClient(
				int clientSocket,
				Autonomous::ObstacleFetcher const &obstacleFetcher,
				Autonomous::Robot const &robotOne,
				Autonomous::Robot const &robotTwo);
		void removeDisconnectedClients();
		void sendObstacles(int clientSocket, Autonomous::ObstacleFetcher const &obstacleFetcher);
		void sendRoute(int clientSocket, std::string const &name, Autonomous::Robot const &robot);
		void sendString(int clientSocket, std::string const &line);
		void log(std::string const &message);

	private:
		Common::Logging::Logger &m_logger;
		bool m_valid;
		int m_serverSocket;
		std::vector<int> m_clientSockets;
		std::vector<int> m_disconnectedClients;
	};
}
}
}

#endif
