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
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:

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


