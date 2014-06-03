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
		CPPUNIT_TEST(isPointInsideField_1cmDistanceToTheEdge_false);
		CPPUNIT_TEST(isPointInsideField_6cmDistanceToTheEdge_true);
		CPPUNIT_TEST_SUITE_END();
	private:
		void isPointInsideField_notInsideField_false();
		void isPointInsideField_onFieldNotInGoalZone_true();
		void isPointInsideField_onFieldAndInGoalZone_false();
		void isPointInsideField_1cmDistanceToTheEdge_false();
		void isPointInsideField_6cmDistanceToTheEdge_true();
	};
}
}
}

#endif
