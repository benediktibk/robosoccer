#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAMTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ENEMYTEAMTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class ReadableRobotMock;
	class StorageMock;
}
namespace Autonomous
{
	class EnemyTeamImpl;

	class EnemyTeamTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(EnemyTeamTest);
		CPPUNIT_TEST(getObstacles_construct_3ObjectsInVector);
		CPPUNIT_TEST(getObstacles_robotsOnPositions_correctCircles);
		CPPUNIT_TEST(getPlayerNextToBall_ballInCenterAndRobot2IsNext_robot2);
		CPPUNIT_TEST(getPlayerNextToBall_ballNearEnemyGoalAndRobot3IsNext_robot3);
		CPPUNIT_TEST(getPlayerNextToBall_ballNearOwnGoalAndRobot1IsNext_robot1);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void getObstacles_construct_3ObjectsInVector();
		void getObstacles_robotsOnPositions_correctCircles();
		void getPlayerNextToBall_ballInCenterAndRobot2IsNext_robot2();
		void getPlayerNextToBall_ballNearEnemyGoalAndRobot3IsNext_robot3();
		void getPlayerNextToBall_ballNearOwnGoalAndRobot1IsNext_robot1();

	private:
		EnemyTeamImpl *m_enemyTeam;
		Abstraction::StorageMock *m_storageMock;
		Abstraction::ReadableRobotMock *m_readableRobotMockPlayer1;
		Abstraction::ReadableRobotMock *m_readableRobotMockPlayer2;
		Abstraction::ReadableRobotMock *m_readableRobotMockPlayer3;


	};
}
}
}

#endif


