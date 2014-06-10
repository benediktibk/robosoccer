#ifndef ROBOSOCCER_COMMON_GEOMETRY_PATHTEST_H
#define ROBOSOCCER_COMMON_GEOMETRY_PATHTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class PathTest :
			public CPPUNIT_NS::TestFixture
	{
		 CPPUNIT_TEST_SUITE(PathTest);
		 CPPUNIT_TEST(intersectsWith_circleIntersectsPathFromLeft_resultIsTrue);
		 CPPUNIT_TEST(intersectsWith_circleIntersectsPathFromRight_resultIsTrue);
		 CPPUNIT_TEST(intersectsWith_circleIntersectsPathFromStart_resultIsTrue);
		 CPPUNIT_TEST(intersectsWith_circleIntersectsPathFromEnd_resultIsTrue);
		 CPPUNIT_TEST(intersectsWith_circleIsInThePath_resultIsTrue);
		 CPPUNIT_TEST(intersectsWith_circlePassesThePath_resultIsFalse);
		 CPPUNIT_TEST(intersectsWith_pathFromRightToLeftAndCircleFarAwayRight_false);
		 CPPUNIT_TEST(intersectsWith_oneBoundaryPostFarAway_false);
		 CPPUNIT_TEST(intersectsWith_oneBoundaryPostFarAwaySimplified_false);
		 CPPUNIT_TEST(intersectsWith_slightlyRotatedButNotIntersecting_true);
		 CPPUNIT_TEST(isCircleOnPath_circleOnPath_true);
		 CPPUNIT_TEST(isCircleOnPath_circleCenterIsNotOnPath_false);
		 CPPUNIT_TEST(getIntersectPoints_circleWithNoIntersects_intersectPointsCountIs0);
		 CPPUNIT_TEST(getIntersectPoints_circleTouchesLine_intersectPointsCountIs1);
		 CPPUNIT_TEST(getIntersectPoints_circleIntersectsLine_intersectPointsCountIs2);
		 CPPUNIT_TEST(getIntersectPoints_circleIntersectsLineFromRight_intersectTypeFromRight);
		 CPPUNIT_TEST(getIntersectPoints_circleIntersectsLineFromRight_intersectPointIs);
		 CPPUNIT_TEST(getAngleBetweenStartAndEnd_StartIs0And0EndIs1And1_AngleIsPiQuarter);
		 CPPUNIT_TEST(getAngleBetweenStartAndEnd_StartIs1And1EndIs0And0_AngleIsMinusPiQuarter);
		 CPPUNIT_TEST(getLeftPerpendicularPoint_pointIs1And2_resultIsCorrect);
		 CPPUNIT_TEST(getRightPerpendicularPoint_pointIs1And2_resultIsCorrect);
		 CPPUNIT_TEST(getDistanceToLeftPerpendicularPoint_pointIs1And2_resultIsCorrect);
		 CPPUNIT_TEST(getDistanceToRightPerpendicularPoint_pointIs1And2_resultIsCorrect);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void intersectsWith_circleIntersectsPathFromLeft_resultIsTrue();
		 void intersectsWith_circleIntersectsPathFromRight_resultIsTrue();
		 void intersectsWith_circleIntersectsPathFromStart_resultIsTrue();
		 void intersectsWith_circleIntersectsPathFromEnd_resultIsTrue();
		 void intersectsWith_circleIsInThePath_resultIsTrue();
		 void intersectsWith_circlePassesThePath_resultIsFalse();
		 void intersectsWith_pathFromRightToLeftAndCircleFarAwayRight_false();
		 void intersectsWith_oneBoundaryPostFarAway_false();
		 void intersectsWith_oneBoundaryPostFarAwaySimplified_false();
		 void intersectsWith_slightlyRotatedButNotIntersecting_true();
		 void isCircleOnPath_circleOnPath_true();
		 void isCircleOnPath_circleCenterIsNotOnPath_false();
		 void getIntersectPoints_circleWithNoIntersects_intersectPointsCountIs0();
		 void getIntersectPoints_circleTouchesLine_intersectPointsCountIs1();
		 void getIntersectPoints_circleIntersectsLine_intersectPointsCountIs2();
		 void getIntersectPoints_circleIntersectsLineFromRight_intersectTypeFromRight();
		 void getIntersectPoints_circleIntersectsLineFromRight_intersectPointIs();
		 void getAngleBetweenStartAndEnd_StartIs0And0EndIs1And1_AngleIsPiQuarter();
		 void getAngleBetweenStartAndEnd_StartIs1And1EndIs0And0_AngleIsMinusPiQuarter();
		 void getLeftPerpendicularPoint_pointIs1And2_resultIsCorrect();
		 void getRightPerpendicularPoint_pointIs1And2_resultIsCorrect();
		 void getDistanceToLeftPerpendicularPoint_pointIs1And2_resultIsCorrect();
		 void getDistanceToRightPerpendicularPoint_pointIs1And2_resultIsCorrect();
	};
}
}
}

#endif
