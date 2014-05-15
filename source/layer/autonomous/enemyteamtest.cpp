#include "layer/autonomous/enemyteamtest.h"
#include "layer/autonomous/enemyteamimpl.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/abstraction/readablerobotmock.h"
#include "layer/abstraction/storagemock.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

void EnemyTeamTest::setUp()
{
	m_storageMock = new StorageMock;
	m_readableRobotMockPlayer1 = &(m_storageMock->getEnemyRobotMock(0));
	m_readableRobotMockPlayer2 = &(m_storageMock->getEnemyRobotMock(1));
	m_readableRobotMockPlayer3 = &(m_storageMock->getEnemyRobotMock(2));
	m_enemyTeam = new EnemyTeamImpl(*m_storageMock);
}

void EnemyTeamTest::tearDown()
{
	delete m_enemyTeam;
	m_enemyTeam = 0;
	delete m_storageMock;
	m_storageMock = 0;
	m_readableRobotMockPlayer1 = 0;
	m_readableRobotMockPlayer2 = 0;
	m_readableRobotMockPlayer3 = 0;
}

void EnemyTeamTest::getObstacles_construct_3ObjectsInVector()
{
	CPPUNIT_ASSERT_EQUAL((size_t) 3, m_enemyTeam->getObstacles().size());
}

void EnemyTeamTest::getPlayerNextToBall_ballInCenterAndRobot2IsNext_robot2()
{
	m_readableRobotMockPlayer1->setPose(Pose(Point(-1.23,-0.3), Angle()));
	m_readableRobotMockPlayer2->setPose(Pose(Point(0.15,0), Angle()));
	m_readableRobotMockPlayer3->setPose(Pose(Point(-0.8,0.23), Angle()));

	IntelligentBallMock ball;
	ball.setPosition(Point(0.02, 0.1));

	CPPUNIT_ASSERT(m_readableRobotMockPlayer2 == &(m_enemyTeam->getPlayerNextToBall(ball)));
}

void EnemyTeamTest::getPlayerNextToBall_ballNearEnemyGoalAndRobot3IsNext_robot3()
{
	m_readableRobotMockPlayer1->setPose(Pose(Point(-0.23,-0.3), Angle()));
	m_readableRobotMockPlayer2->setPose(Pose(Point(0.15,0), Angle()));
	m_readableRobotMockPlayer3->setPose(Pose(Point(-1.25,0.23), Angle()));

	IntelligentBallMock ball;
	ball.setPosition(Point(-1.12, -0.1));

	CPPUNIT_ASSERT(m_readableRobotMockPlayer3 == &(m_enemyTeam->getPlayerNextToBall(ball)));
}

void EnemyTeamTest::getPlayerNextToBall_ballNearOwnGoalAndRobot1IsNext_robot1()
{
	m_readableRobotMockPlayer1->setPose(Pose(Point(1.23,-0.05), Angle()));
	m_readableRobotMockPlayer2->setPose(Pose(Point(0.15,0), Angle()));
	m_readableRobotMockPlayer3->setPose(Pose(Point(-0.8,0.23), Angle()));

	IntelligentBallMock ball;
	ball.setPosition(Point(1.02, 0.3));

	CPPUNIT_ASSERT(m_readableRobotMockPlayer1 == &(m_enemyTeam->getPlayerNextToBall(ball)));
}

void EnemyTeamTest::getObstacles_robotsOnPositions_correctCircles()
{
	m_readableRobotMockPlayer1->setPose(Pose(Point(1.23,-0.05), Angle()));
	m_readableRobotMockPlayer2->setPose(Pose(Point(0.15,0), Angle()));
	m_readableRobotMockPlayer3->setPose(Pose(Point(-0.8,0.23), Angle()));

	const vector<Circle> &obstacles = m_enemyTeam->getObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t) 3, obstacles.size());

	for (int i = 0; i < 3; ++i)
		CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1, obstacles[i].getDiameter(), 0.05);
}
