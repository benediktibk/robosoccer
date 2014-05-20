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
		CPPUNIT_TEST(getAllObstacles_empty_countIs6);
		CPPUNIT_TEST(getAllObstacles_empty_allObstaclesContained);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void getAllObstacles_empty_countIs6();
		void getAllObstacles_empty_allObstaclesContained();

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
