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
		CPPUNIT_TEST(isPointInsideField_pointInNeutralZone_true);
		CPPUNIT_TEST(isPointInsideField_pointOutsideField_false);
		CPPUNIT_TEST(isPointInsideField_pointInOwnGoalZone_true);
		CPPUNIT_TEST(isPointInsideField_pointInEnemyGoalZone_false);
		CPPUNIT_TEST_SUITE_END();
	private:

		void isPointInsideField_pointInNeutralZone_true();
		void isPointInsideField_pointOutsideField_false();
		void isPointInsideField_pointInOwnGoalZone_true();
		void isPointInsideField_pointInEnemyGoalZone_false();

	};
}
}
}

#endif


