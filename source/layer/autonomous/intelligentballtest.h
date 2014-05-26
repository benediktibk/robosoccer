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
		CPPUNIT_TEST(getMovingDirection_isLeft_Fieldsideleft);
		CPPUNIT_TEST(getMovingDirection_isRight_FielsideRight);
		CPPUNIT_TEST(getCurrentFieldSide_isLeft_FieldsideLeft);
		CPPUNIT_TEST(getCurrentFieldSide_isRight_FieldsideRight);
		CPPUNIT_TEST(getObstacle_empty_sameAsFromBall);
		CPPUNIT_TEST(getObstacles_empty_oneElementWhichIsSameAsFromBall);
		CPPUNIT_TEST(getShootingLineCoveragePercent_isZero_0);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void isMoving_movingFast_true();
		void isMoving_notMoving_false();
		void getPosition_shouldbe_5_5();
		void getRotation_shouldbe_1();
		void getMovingDirection_isLeft_Fieldsideleft();
		void getMovingDirection_isRight_FielsideRight();
		void getCurrentFieldSide_isLeft_FieldsideLeft();
		void getCurrentFieldSide_isRight_FieldsideRight();
		void getObstacle_empty_sameAsFromBall();
		void getObstacles_empty_oneElementWhichIsSameAsFromBall();
		void getShootingLineCoveragePercent_isZero_0();

	private:
		Abstraction::BallMock *m_ballMock;
		Autonomous::IntelligentBallImpl *m_intelligentBall;
	};
}
}
}

#endif


