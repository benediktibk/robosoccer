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
		CPPUNIT_TEST(getAllObstacles_12obstaclesInTotal_countIs12);
		CPPUNIT_TEST(getAllObstacles_6obstaclesInTotal_allObstaclesContained);
		CPPUNIT_TEST(getAllObstaclesButMe_firstRobot_countIs11);
		CPPUNIT_TEST(getAllObstaclesButMe_firstRobot_allObstaclesButOwnContained);
		CPPUNIT_TEST(getAllObstaclesButMe_secondRobot_countIs11);
		CPPUNIT_TEST(getAllObstaclesButMe_secondRobot_allObstaclesButOwnContained);
		CPPUNIT_TEST(getAllObstaclesButMeInRange_firstRobotAndFarAwayFromAllOtherObstacles_countIs0);
		CPPUNIT_TEST(getAllObstaclesButMeInRange_firstRobotAndCloseToBall_oneCorrectElement);
		CPPUNIT_TEST(defineBall_noBallDefined_getAllObstaclesButMeAndBallInRangeReturnsAllObstacles);
		CPPUNIT_TEST(defineBall_ballDefined_getAllObstablesButMeAndBallInRangeReturnsOneLess);
		CPPUNIT_TEST(getAllObstaclesButMeAndBallInRange_ballNotInRange_noObstacles);
		CPPUNIT_TEST(getAllObstaclesButMeAndBallInRange_ballInRange_noObstacles);
		CPPUNIT_TEST(getAllObstaclesButMeAndBallInRange_otherObstacleInRange_oneCorrectObstacle);
		CPPUNIT_TEST(getAllObstaclesBugMeAndBallInRange_selfInRange_noObstacles);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void getAllObstacles_12obstaclesInTotal_countIs12();
		void getAllObstacles_6obstaclesInTotal_allObstaclesContained();
		void getAllObstaclesButMe_firstRobot_countIs11();
		void getAllObstaclesButMe_firstRobot_allObstaclesButOwnContained();
		void getAllObstaclesButMe_secondRobot_countIs11();
		void getAllObstaclesButMe_secondRobot_allObstaclesButOwnContained();
		void getAllObstaclesButMeInRange_firstRobotAndFarAwayFromAllOtherObstacles_countIs0();
		void getAllObstaclesButMeInRange_firstRobotAndCloseToBall_oneCorrectElement();
		void getAllObstaclesButMeInRange_firstRobotAndNearlyCloseEnoughToBall_countIs0();
		void defineBall_noBallDefined_getAllObstaclesButMeAndBallInRangeReturnsAllObstacles();
		void defineBall_ballDefined_getAllObstablesButMeAndBallInRangeReturnsOneLess();
		void getAllObstaclesButMeAndBallInRange_ballNotInRange_noObstacles();
		void getAllObstaclesButMeAndBallInRange_ballInRange_noObstacles();
		void getAllObstaclesButMeAndBallInRange_otherObstacleInRange_oneCorrectObstacle();
		void getAllObstaclesBugMeAndBallInRange_selfInRange_noObstacles();

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
