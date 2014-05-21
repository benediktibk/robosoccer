#ifndef ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERGOALKEEPERTEST_H
#define ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERGOALKEEPERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Layer
{
namespace Main
{
	class FieldPositionCheckerGoalkeeperTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldPositionCheckerGoalkeeperTest);
		CPPUNIT_TEST(isPointInsideField_pointOutsideField_false);
		CPPUNIT_TEST(isPointInsideField_rightSidePointInOwnGoalZone_true);
		CPPUNIT_TEST(isPointInsideField_rightSidePointInEnemyGoalZone_false);
		CPPUNIT_TEST(isPointInsideField_leftSidePointInOwnGoalZone_true);
		CPPUNIT_TEST(isPointInsideField_leftSidePointInEnemyGoalZone_false);
		CPPUNIT_TEST(isPointInsideField_changingSidesInGoalZone_falseThenTrue);
		CPPUNIT_TEST_SUITE_END();

	private:
		void isPointInsideField_pointOutsideField_false();
		void isPointInsideField_rightSidePointInOwnGoalZone_true();
		void isPointInsideField_rightSidePointInEnemyGoalZone_false();
		void isPointInsideField_leftSidePointInOwnGoalZone_true();
		void isPointInsideField_leftSidePointInEnemyGoalZone_false();
		void isPointInsideField_changingSidesInGoalZone_falseThenTrue();

	};
}
}
}

#endif


