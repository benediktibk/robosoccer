#include "layer/autonomous/obstaclefetchertest.h"
#include "layer/autonomous/obstaclefetcherimpl.h"
#include "layer/autonomous/obstaclesourcemock.h"
#include <algorithm>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

void ObstacleFetcherTest::setUp()
{
	m_firstRobot = new ObstacleSourceMock();
	m_secondRobot = new ObstacleSourceMock();
	m_enemyTeam = new ObstacleSourceMock();
	m_ball = new ObstacleSourceMock();
	m_obstacleFetcher = new ObstacleFetcherImpl();
	vector<Circle> firstRobotObstacles;
	firstRobotObstacles.push_back(Circle(Point(1, 1), 1));
	m_firstRobot->setObstacles(firstRobotObstacles);
	vector<Circle> secondRobotObstacles;
	secondRobotObstacles.push_back(Circle(Point(2, 2), 2));
	m_secondRobot->setObstacles(secondRobotObstacles);
	vector<Circle> enemyObstacles;
	enemyObstacles.push_back(Circle(Point(4, 4), 4));
	enemyObstacles.push_back(Circle(Point(5, 5), 5));
	enemyObstacles.push_back(Circle(Point(6, 6), 6));
	m_enemyTeam->setObstacles(enemyObstacles);
	vector<Circle> ballObstacles;
	ballObstacles.push_back(Circle(Point(7, 7), 7));
	m_ball->setObstacles(ballObstacles);
	m_obstacleFetcher->addSource(*m_firstRobot);
	m_obstacleFetcher->addSource(*m_secondRobot);
	m_obstacleFetcher->addSource(*m_enemyTeam);
	m_obstacleFetcher->addSource(*m_ball);
}

void ObstacleFetcherTest::tearDown()
{
	delete m_obstacleFetcher;
	m_obstacleFetcher = 0;
	delete m_firstRobot;
	m_firstRobot = 0;
	delete m_secondRobot;
	m_secondRobot = 0;
	delete m_enemyTeam;
	m_enemyTeam = 0;
	delete m_ball;
	m_ball = 0;
}

void ObstacleFetcherTest::getAllObstacles_6obstaclesInTotal_countIs6()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)6, obstacles.size());
}

void ObstacleFetcherTest::getAllObstacles_6obstaclesInTotal_allObstaclesContained()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstacles();

	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(1, 1), 1)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(2, 2), 2)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(4, 4), 4)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(5, 5), 5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(6, 6), 6)));
}

void ObstacleFetcherTest::getAllObstaclesButMe_firstRobot_countIs5()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMe(*m_firstRobot);

	CPPUNIT_ASSERT_EQUAL((size_t)5, obstacles.size());
}

void ObstacleFetcherTest::getAllObstaclesButMe_firstRobot_allObstaclesButOwnContained()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMe(*m_firstRobot);

	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(2, 2), 2)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(4, 4), 4)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(5, 5), 5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(6, 6), 6)));
}

void ObstacleFetcherTest::getAllObstaclesButMe_secondRobot_countIs5()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMe(*m_secondRobot);

	CPPUNIT_ASSERT_EQUAL((size_t)5, obstacles.size());
}

void ObstacleFetcherTest::getAllObstaclesButMe_secondRobot_allObstaclesButOwnContained()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMe(*m_secondRobot);

	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(1, 1), 1)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(4, 4), 4)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(5, 5), 5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(6, 6), 6)));
}
