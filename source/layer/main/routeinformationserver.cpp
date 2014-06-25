#include "layer/main/routeinformationserver.h"
#include "layer/autonomous/obstaclefetcher.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/obstaclesource.h"
#include "layer/abstraction/tcpserversocket.h"
#include "common/geometry/circle.h"
#include "common/geometry/pose.h"
#include "common/routing/route.h"
#include "common/logging/logger.h"
#include <sstream>
#include <assert.h>

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Routing;
using namespace RoboSoccer::Common::Logging;
using namespace std;

RouteInformationServer::RouteInformationServer(Abstraction::TCPServerSocket &socket) :
	m_socket(socket)
{
	assert(socket.isValid());
}

void RouteInformationServer::updateClients(const ObstacleFetcher &obstacleFetcher,
		const Robot &robotOne, const Robot &robotTwo, const ObstacleSource &goalkeeper)
{
	m_socket.updateClients();
	sendObstacles(obstacleFetcher, goalkeeper);
	sendRouteAndTargets("robot one", robotOne);
	sendRouteAndTargets("robot two", robotTwo);
}

void RouteInformationServer::sendObstacles(const ObstacleFetcher &obstacleFetcher, const ObstacleSource &goalkeeper)
{
	vector<Circle> obstacles = obstacleFetcher.getAllObstaclesButOwnTeamAndGoalObstacles();
	obstacles.push_back(goalkeeper.getObstacles().front());
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
	m_socket.sendString(stream.str());
}

void RouteInformationServer::sendRouteAndTargets(string const &name, Robot const &robot)
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

	stream << "targets:" << endl;
	vector<Pose> targets = robot.getCurrentTargets();
	for (vector<Pose>::const_iterator i = targets.begin(); i != targets.end(); ++i)
	{
		Pose const &target = *i;
		stream << target.getPosition() << endl;
	}

	stream << endl;
	m_socket.sendString(stream.str());
}
