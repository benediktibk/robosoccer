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
	class ObstacleFetcherImpl;
	class TeamMock;
	class EnemyTeamMock;
	class IntelligentBallMock;

	class ObstacleFetcherTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(ObstacleFetcherTest);
		CPPUNIT_TEST(getAllObstacles_empty_countIs7);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void getAllObstacles_empty_countIs7();

	private:
		ObstacleFetcherImpl *m_obstacleFetcher;
		TeamMock *m_team;
		EnemyTeamMock *m_enemyTeam;
		IntelligentBallMock *m_ball;
	};
}
}
}

#endif
