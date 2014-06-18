#include "layer/main/routeinformationserver.h"
#include "layer/autonomous/obstaclefetcher.h"
#include "layer/autonomous/robot.h"
#include "common/geometry/circle.h"
#include "common/routing/route.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sstream>
#include <string.h>

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Routing;
using namespace std;

RouteInformationServer::RouteInformationServer(unsigned int port)
{
	sockaddr_in serverAddress;
	m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_serverSocket < 0)
	{
		m_valid = false;
		return;
	}
	else
		m_valid = true;

	if (port < 1024 || port > 49151)
	{
		m_valid = false;
		return;
	}

	// set the struct to zero
	bzero((char *)&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	// accept connections on all addresses
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);

	int bindResult = bind(m_serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress));

	if (bindResult < 0)
	{
		m_valid = false;
		return;
	}

	listen(m_serverSocket, 10);
	fcntl(m_serverSocket, F_SETFL, O_NONBLOCK);
}

RouteInformationServer::~RouteInformationServer()
{
	for (vector<int>::const_iterator i = m_clientSockets.begin(); i != m_clientSockets.end(); ++i)
		close(*i);
	m_clientSockets.clear();
	close(m_serverSocket);
	m_serverSocket = -1;
}

void RouteInformationServer::updateClients(
		const ObstacleFetcher &obstacleFetcher,
		const Robot &robotOne, const Robot &robotTwo)
{
	acceptNewClients();

	for (vector<int>::const_iterator i = m_clientSockets.begin(); i != m_clientSockets.end(); ++i)
		updateClient(*i, obstacleFetcher, robotOne, robotTwo);
}

bool RouteInformationServer::isValid() const
{
	return m_valid;
}

void RouteInformationServer::acceptNewClients()
{
	sockaddr_in clientAddress;
	int clientSocket;
	int size = sizeof(clientAddress);

	do
	{
		clientSocket = accept(
					m_serverSocket,
					reinterpret_cast<sockaddr*>(&clientAddress),
					reinterpret_cast<socklen_t*>(&size));

		if (clientSocket != 0)
			m_clientSockets.push_back(clientSocket);
	} while(clientSocket != 0);
}

void RouteInformationServer::updateClient(
		int clientSocket, const ObstacleFetcher &obstacleFetcher,
		const Robot &robotOne, const Robot &robotTwo)
{
	sendObstacles(clientSocket, obstacleFetcher);
	sendRoute(clientSocket, "robot one", robotOne);
	sendRoute(clientSocket, "robot two", robotTwo);
}

void RouteInformationServer::sendObstacles(int clientSocket, const ObstacleFetcher &obstacleFetcher)
{
	vector<Circle> obstacles = obstacleFetcher.getAllObstacles();
	stringstream stream;
	stream << "obstacles" << endl;

	for (vector<Circle>::const_iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		Circle const &circle = *i;
		Point const &position = circle.getCenter();
		double diameter = circle.getDiameter();
		double radius = diameter/2;
		stream << position << ", " << radius << endl;
	}

	stream << endl;
	sendString(clientSocket, stream.str());
}

void RouteInformationServer::sendRoute(int clientSocket, string const &name, Robot const &robot)
{
	Route route = robot.getCurrentRoute();
	stringstream stream;
	stream << name << endl;
	stream << "width: " << route.getWidth() << endl;
	list<Point> points = route.getAllPoints();

	for (list<Point>::const_iterator i = points.begin(); i != points.end(); ++i)
	{
		Point const &point = *i;
		stream << point << endl;
	}

	stream << endl;
	sendString(clientSocket, stream.str());
}

void RouteInformationServer::sendString(int clientSocket, const string &data)
{
	const char *dataPointer = data.c_str();
	write(clientSocket, dataPointer, data.size() + 1);
}
