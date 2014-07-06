#ifndef ROBOSOCCER_LAYER_ABSTRACTION_FIELDPOSITIONCHECKERTEST_H
#define ROBOSOCCER_LAYER_ABSTRACTION_FIELDPOSITIONCHECKERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class FieldPositionCheckerTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldPositionCheckerTest);
		CPPUNIT_TEST(isPointInsideGoalZone_atFrontEdgeOfLeftGoal_false);
		CPPUNIT_TEST(isPointInsideGoalZone_atLeftEdgeOfLeftGoal_false);
		CPPUNIT_TEST(isPointInsideGoalZone_atRightEdgeOfLeftGoal_false);
		CPPUNIT_TEST(isPointInsideGoalZone_atFrontEdgeOfRightGoal_false);
		CPPUNIT_TEST(isPointInsideGoalZone_atLeftEdgeOfRightGoal_false);
		CPPUNIT_TEST(isPointInsideGoalZone_atRightEdgeOfRightGoal_false);
		CPPUNIT_TEST(isPointInsideGoalZone_inMiddleOfLeftGoalZone_true);
		CPPUNIT_TEST(isPointInsideGoalZone_inMiddleOfRightGoalZone_true);
		CPPUNIT_TEST_SUITE_END();

	private:
		void isPointInsideGoalZone_atFrontEdgeOfLeftGoal_false();
		void isPointInsideGoalZone_atLeftEdgeOfLeftGoal_false();
		void isPointInsideGoalZone_atRightEdgeOfLeftGoal_false();
		void isPointInsideGoalZone_atFrontEdgeOfRightGoal_false();
		void isPointInsideGoalZone_atLeftEdgeOfRightGoal_false();
		void isPointInsideGoalZone_atRightEdgeOfRightGoal_false();
		void isPointInsideGoalZone_inMiddleOfLeftGoalZone_true();
		void isPointInsideGoalZone_inMiddleOfRightGoalZone_true();
	};
}
}
}

#endif
