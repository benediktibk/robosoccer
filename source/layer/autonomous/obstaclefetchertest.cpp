#include "layer/autonomous/obstaclefetchertest.h"
#include "layer/autonomous/obstaclefetcherimpl.h"
#include "layer/autonomous/obstaclesourcemock.h"
#include <algorithm>
#include <iostream>

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
	firstRobotObstacles.push_back(Circle(Point(1, 1), 0.5));
	m_firstRobot->setObstacles(firstRobotObstacles);
	vector<Circle> secondRobotObstacles;
	secondRobotObstacles.push_back(Circle(Point(2, 2), 0.5));
	m_secondRobot->setObstacles(secondRobotObstacles);
	vector<Circle> enemyObstacles;
	enemyObstacles.push_back(Circle(Point(4, 4), 0.5));
	enemyObstacles.push_back(Circle(Point(5, 5), 0.5));
	enemyObstacles.push_back(Circle(Point(6, 6), 0.5));
	m_enemyTeam->setObstacles(enemyObstacles);
	vector<Circle> ballObstacles;
	ballObstacles.push_back(Circle(Point(7, 7), 0.5));
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

void ObstacleFetcherTest::getAllObstacles_12obstaclesInTotal_countIs12()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)12, obstacles.size());
}

void ObstacleFetcherTest::getAllObstacles_6obstaclesInTotal_allObstaclesContained()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstacles();

	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(1, 1), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(2, 2), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(4, 4), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(5, 5), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(6, 6), 0.5)));
}

void ObstacleFetcherTest::getAllObstaclesButMe_firstRobot_countIs11()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMe(*m_firstRobot, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)11, obstacles.size());
}

void ObstacleFetcherTest::getAllObstaclesButMe_firstRobot_allObstaclesButOwnContained()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMe(*m_firstRobot, 1);

	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(2, 2), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(4, 4), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(5, 5), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(6, 6), 0.5)));
}

void ObstacleFetcherTest::getAllObstaclesButMe_secondRobot_countIs11()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMe(*m_secondRobot, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)11, obstacles.size());
}

void ObstacleFetcherTest::getAllObstaclesButMe_secondRobot_allObstaclesButOwnContained()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMe(*m_secondRobot, 1);

	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(1, 1), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(4, 4), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(5, 5), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(6, 6), 0.5)));
}

void ObstacleFetcherTest::getAllObstaclesButMeInRange_firstRobotAndFarAwayFromAllOtherObstacles_countIs0()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeInRange(*m_firstRobot, Point(10, 10), 0.5, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void ObstacleFetcherTest::getAllObstaclesButMeInRange_firstRobotAndCloseToBall_oneCorrectElement()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeInRange(*m_firstRobot, Point(7.7, 7), 0.5, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
	CPPUNIT_ASSERT_EQUAL(Circle(Point(7, 7), 0.5), obstacles.front());
}

void ObstacleFetcherTest::getAllObstaclesButMeInRange_firstRobotAndNearlyCloseEnoughToBall_countIs0()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeInRange(*m_firstRobot, Point(7.8, 7), 0.5, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void ObstacleFetcherTest::defineBall_noBallDefined_getAllObstaclesButMeAndBallInRangeReturnsAllObstacles()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeAndBallInRange(*m_firstRobot, Point(0, 0), 100, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)11, obstacles.size());
}

void ObstacleFetcherTest::defineBall_ballDefined_getAllObstablesButMeAndBallInRangeReturnsOneLess()
{
	m_obstacleFetcher->defineBall(*m_ball);

	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeAndBallInRange(*m_firstRobot, Point(0, 0), 100, 1);
	CPPUNIT_ASSERT_EQUAL((size_t)10, obstacles.size());
}

void ObstacleFetcherTest::getAllObstaclesButMeAndBallInRange_ballNotInRange_noObstacles()
{
	m_obstacleFetcher->defineBall(*m_ball);

	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeAndBallInRange(*m_firstRobot, Point(8, 8), 0.1, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void ObstacleFetcherTest::getAllObstaclesButMeAndBallInRange_ballInRange_noObstacles()
{
	m_obstacleFetcher->defineBall(*m_ball);

	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeAndBallInRange(*m_firstRobot, Point(7.2, 7.2), 0.5, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void ObstacleFetcherTest::getAllObstaclesButMeAndBallInRange_otherObstacleInRange_oneCorrectObstacle()
{
	m_obstacleFetcher->defineBall(*m_ball);

	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeAndBallInRange(*m_firstRobot, Point(6.2, 6.2), 0.5, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(6, 6), 0.5)));
}

void ObstacleFetcherTest::getAllObstaclesBugMeAndBallInRange_selfInRange_noObstacles()
{
	m_obstacleFetcher->defineBall(*m_ball);

	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeAndBallInRange(*m_firstRobot, Point(1.2, 1.2), 0.5, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void ObstacleFetcherTest::getAllObstaclesButMeAndGoalObstacles_firstRobot_countIs5()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeAndGoalObstacles(*m_firstRobot, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)5, obstacles.size());
}

void ObstacleFetcherTest::getAllObstaclesButMeAndGoalObstacles_firstRobot_allObstaclesButOwnAndGoalContained()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeAndGoalObstacles(*m_firstRobot, 1);

	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(2, 2), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(4, 4), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(5, 5), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(6, 6), 0.5)));
}

void ObstacleFetcherTest::getAllObstaclesButMeAndGoalObstacles_secondRobot_countIs5()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeAndGoalObstacles(*m_secondRobot, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)5, obstacles.size());
}

void ObstacleFetcherTest::getAllObstaclesButMeAndGoalObstacles_secondRobot_allObstaclesButOwnAndGoalContained()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeAndGoalObstacles(*m_secondRobot, 1);

	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(1, 1), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(4, 4), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(5, 5), 0.5)));
	CPPUNIT_ASSERT(1 == count(obstacles.begin(), obstacles.end(), Circle(Point(6, 6), 0.5)));
}

void ObstacleFetcherTest::getAllObstaclesButMeAndGoalObstaclesInRange_firstRobotAndFarAwayFromAllOtherObstacles_countIs0()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeInRange(*m_firstRobot, Point(10, 10), 0.5, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void ObstacleFetcherTest::getAllObstaclesButMeAndGoalObstaclesInRange_firstRobotAndCloseToBall_oneCorrectElement()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeInRange(*m_firstRobot, Point(7.7, 7), 0.5, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
	CPPUNIT_ASSERT_EQUAL(Circle(Point(7, 7), 0.5), obstacles.front());
}

void ObstacleFetcherTest::getAllObstaclesButMeAndGoalObstaclesInRange_firstRobotAndNearlyCloseEnoughToBall_countIs0()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeInRange(*m_firstRobot, Point(7.8, 7), 0.5, 1);

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void ObstacleFetcherTest::getAllObstablesButMeAndBallInRange_goalObstaclesNoChangedSize()
{
	m_obstacleFetcher->defineBall(*m_ball);
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeAndBallInRange(*m_firstRobot, Point(0, 0), 100, 10);
	int counter = 0;
	for (vector<Circle>::const_iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		Circle circle = *i;
		double diameter = circle.getDiameter();
		if(diameter == 0.25)
			counter++;
	}
	CPPUNIT_ASSERT_EQUAL(6, counter);
}

void ObstacleFetcherTest::getAllObstablesButMeInRange_goalObstaclesNoChangedSize()
{
	m_obstacleFetcher->defineBall(*m_ball);
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstaclesButMeInRange(*m_firstRobot, Point(0, 0), 100, 10);
	int counter = 0;
	for (vector<Circle>::const_iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		Circle circle = *i;
		double diameter = circle.getDiameter();
		cout << diameter << endl;
		if(diameter == 0.25)
			counter++;
	}
	CPPUNIT_ASSERT_EQUAL(6, counter);
}
