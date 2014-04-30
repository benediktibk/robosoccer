#ifndef ROBOSOCCER_COMMON_GEOMETRY_LINETEST_H
#define ROBOSOCCER_COMMON_GEOMETRY_LINETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class LineTest :
			public CPPUNIT_NS::TestFixture
	{
		 CPPUNIT_TEST_SUITE(LineTest);
		 CPPUNIT_TEST(getIntersectPoints_circleWithNoIntersects_intersectPointsCountIs0);
		 CPPUNIT_TEST(getIntersectPoints_circleToutchesLine_intersectPointsCountIs1);
		 CPPUNIT_TEST(getIntersectPoints_circleIntersectsLine_intersectPointsCountIs2);
		 CPPUNIT_TEST(getIntersectPoints_circleToutchesLineAt0And2_intersectPointsIs0And2);
		 CPPUNIT_TEST(getIntersectPoints_circleIntersectsLineAtMinus1And1_intersectPointsIsMinus1And1);
		 CPPUNIT_TEST(getIntersectPoints_circleIntersectsLineAt1And1_intersectPointsIs1And1);
		 CPPUNIT_TEST(getIntersectPoints_circleAt1And1IntersectsLineAt2And2_intersectPointsIs2And2);
		 CPPUNIT_TEST(getIntersectPoints_lineIsVertical_intersectPointIsMinus1AndMinus1);
		 CPPUNIT_TEST(getIntersectPoints_lineIsVerticalAndCircleIsNotAt0And0_intersectPointIs2And2);
		 CPPUNIT_TEST(getIntersectPoints_circleBehindEndPointWithNoIntersects_intersectPointsCountIs0);
		 CPPUNIT_TEST(getIntersectPoints_circleOverEndPointWithNoIntersects_intersectPointsCountIs0);
		 CPPUNIT_TEST(getIntersectPoints_circleIntersectsLineButOnlyTheSmallerPointIsOnTheLine_intersectPointsCountIs2);
		 CPPUNIT_TEST(getIntersectPoints_circleIntersectsLineButOnlyTheHigherPointIsOnTheLine_intersectPointsCountIs2);
		 CPPUNIT_TEST(isTargetPointRightOfLine_rightOfLine_true);
		 CPPUNIT_TEST(isTargetPointRightOfLine_leftOfLine_false);
		 CPPUNIT_TEST(getPerpendicularPoint_pointIs1And2_resultIsCorrect);
		 CPPUNIT_TEST(getPerpendicularPoint_pointIs1p5And2_resultIsCorrect);
		 CPPUNIT_TEST(isOnePointLeftAndOneRightOfLine_strangeExample_resultIsTrue);
		 CPPUNIT_TEST(shiftParallel_shiftLine_resultIsCorrect);
		 CPPUNIT_TEST(getPointOnDirectionOfLine_percentOfLenghtOfLineIs0_resultIsStart);
		 CPPUNIT_TEST(getPointOnDirectionOfLine_percentOfLenghtOfLineIs1_resultIsEnd);
		 CPPUNIT_TEST(getPointOnDirectionOfLine_percentOfLenghtOfLineIs2_resultIsCorrect);
		 CPPUNIT_TEST(getIntersectPoint_linesAreParralel_noIntersect);
		 CPPUNIT_TEST(getIntersectPoint_linesAreVerticalButNotToutching_noIntersect);
		 CPPUNIT_TEST(getIntersectPoint_linesAreVerticalAndIntersecting_oneIntersect);
		 CPPUNIT_TEST(getIntersectPoint_linesAreIntersecting_oneIntersect);
		 CPPUNIT_TEST(getIntersectPoint_linesAreToutching_oneIntersect);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void getIntersectPoints_circleWithNoIntersects_intersectPointsCountIs0();
		 void getIntersectPoints_circleToutchesLine_intersectPointsCountIs1();
		 void getIntersectPoints_circleIntersectsLine_intersectPointsCountIs2();
		 void getIntersectPoints_circleToutchesLineAt0And2_intersectPointsIs0And2();
		 void getIntersectPoints_circleIntersectsLineAtMinus1And1_intersectPointsIsMinus1And1();
		 void getIntersectPoints_circleIntersectsLineAt1And1_intersectPointsIs1And1();
		 void getIntersectPoints_circleAt1And1IntersectsLineAt2And2_intersectPointsIs2And2();
		 void getIntersectPoints_lineIsVertical_intersectPointIsMinus1AndMinus1();
		 void getIntersectPoints_lineIsVerticalAndCircleIsNotAt0And0_intersectPointIs2And2();
		 void getIntersectPoints_circleBehindEndPointWithNoIntersects_intersectPointsCountIs0();
		 void getIntersectPoints_circleOverEndPointWithNoIntersects_intersectPointsCountIs0();
		 void getIntersectPoints_circleIntersectsLineButOnlyTheSmallerPointIsOnTheLine_intersectPointsCountIs2();
		 void getIntersectPoints_circleIntersectsLineButOnlyTheHigherPointIsOnTheLine_intersectPointsCountIs2();
		 void isTargetPointRightOfLine_rightOfLine_true();
		 void isTargetPointRightOfLine_leftOfLine_false();
		 void getPerpendicularPoint_pointIs1And2_resultIsCorrect();
		 void getPerpendicularPoint_pointIs1p5And2_resultIsCorrect();
		 void isOnePointLeftAndOneRightOfLine_strangeExample_resultIsTrue();
		 void shiftParallel_shiftLine_resultIsCorrect();
		 void getPointOnDirectionOfLine_percentOfLenghtOfLineIs0_resultIsStart();
		 void getPointOnDirectionOfLine_percentOfLenghtOfLineIs1_resultIsEnd();
		 void getPointOnDirectionOfLine_percentOfLenghtOfLineIs2_resultIsCorrect();
		 void getIntersectPoint_linesAreParralel_noIntersect();
		 void getIntersectPoint_linesAreVerticalButNotToutching_noIntersect();
		 void getIntersectPoint_linesAreVerticalAndIntersecting_oneIntersect();
		 void getIntersectPoint_linesAreIntersecting_oneIntersect();
		 void getIntersectPoint_linesAreToutching_oneIntersect();

	};
}
}
}

#endif
