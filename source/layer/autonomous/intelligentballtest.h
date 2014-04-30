#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_INTELLIGENTBALLTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_INTELLIGENTBALLTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class BallMock;
}
namespace Autonomous
{
	class IntelligentBallImpl;
	class IntelligentBallTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(IntelligentBallTest);
		CPPUNIT_TEST(isMoving_movingFast_true);
		CPPUNIT_TEST(isMoving_notMoving_false);
		CPPUNIT_TEST(getPosition_shouldbe_5_5);
		CPPUNIT_TEST(getRotation_shouldbe_1);
		CPPUNIT_TEST(getMovingDirection_shouldbe_Left);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void isMoving_movingFast_true();
		void isMoving_notMoving_false();
		void getPosition_shouldbe_5_5();
		void getRotation_shouldbe_1();
		void getMovingDirection_shouldbe_Left();
	private:
		Abstraction::BallMock *m_ballMock;
		Autonomous::IntelligentBallImpl *m_intelligentBall;
	};
}
}
}

#endif


