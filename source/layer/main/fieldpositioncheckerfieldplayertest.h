#ifndef ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERFIELDPLAYERTEST_H
#define ROBOSOCCER_LAYER_MAIN_FIELDPOSITIONCHECKERFIELDPLAYERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Layer
{
namespace Main
{
	class FieldPositionCheckerFieldPlayerTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldPositionCheckerFieldPlayerTest);
		CPPUNIT_TEST(isPointInsideField_notInsideField_false);
		CPPUNIT_TEST(isPointInsideField_onFieldNotInGoalZone_true);
		CPPUNIT_TEST(isPointInsideField_onFieldAndInGoalZone_false);
		CPPUNIT_TEST(isPointInsideField_1cmDistanceToLeftEdge_false);
		CPPUNIT_TEST(isPointInsideField_6cmDistanceToLeftEdge_true);
		CPPUNIT_TEST(isPointInsideField_1cmDistanceToRightEdge_false);
		CPPUNIT_TEST(isPointInsideField_6cmDistanceToRightEdge_true);
		CPPUNIT_TEST(isPointInsideField_1cmDistanceToLeftEndSide_false);
		CPPUNIT_TEST(isPointInsideField_6cmDistanceToLeftEndSide_true);
		CPPUNIT_TEST(isPointInsideField_1cmDistanceToRightEndSide_false);
		CPPUNIT_TEST(isPointInsideField_6cmDistanceToRightEndSide_true);
		CPPUNIT_TEST_SUITE_END();
	private:
		void isPointInsideField_notInsideField_false();
		void isPointInsideField_onFieldNotInGoalZone_true();
		void isPointInsideField_onFieldAndInGoalZone_false();
		void isPointInsideField_1cmDistanceToLeftEdge_false();
		void isPointInsideField_6cmDistanceToLeftEdge_true();
		void isPointInsideField_1cmDistanceToRightEdge_false();
		void isPointInsideField_6cmDistanceToRightEdge_true();
		void isPointInsideField_1cmDistanceToLeftEndSide_false();
		void isPointInsideField_6cmDistanceToLeftEndSide_true();
		void isPointInsideField_1cmDistanceToRightEndSide_false();
		void isPointInsideField_6cmDistanceToRightEndSide_true();
	};
}
}
}

#endif
