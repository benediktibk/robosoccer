#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHERTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class ObstacleFetcher;
	class ObstacleSourceMock;

	class ObstacleFetcherTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(ObstacleFetcherTest);
		CPPUNIT_TEST(getAllObstacles_6obstaclesInTotal_countIs6);
		CPPUNIT_TEST(getAllObstacles_6obstaclesInTotal_allObstaclesContained);
		CPPUNIT_TEST(getAllObstaclesButMe_firstRobot_countIs5);
		CPPUNIT_TEST(getAllObstaclesButMe_firstRobot_allObstaclesButOwnContained);
		CPPUNIT_TEST(getAllObstaclesButMe_secondRobot_countIs5);
		CPPUNIT_TEST(getAllObstaclesButMe_secondRobot_allObstaclesButOwnContained);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void getAllObstacles_6obstaclesInTotal_countIs6();
		void getAllObstacles_6obstaclesInTotal_allObstaclesContained();
		void getAllObstaclesButMe_firstRobot_countIs5();
		void getAllObstaclesButMe_firstRobot_allObstaclesButOwnContained();
		void getAllObstaclesButMe_secondRobot_countIs5();
		void getAllObstaclesButMe_secondRobot_allObstaclesButOwnContained();

	private:
		ObstacleFetcher *m_obstacleFetcher;
		ObstacleSourceMock *m_firstRobot;
		ObstacleSourceMock *m_secondRobot;
		ObstacleSourceMock *m_enemyTeam;
		ObstacleSourceMock *m_ball;
	};
}
}
}

#endif
