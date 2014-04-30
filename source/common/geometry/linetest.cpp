#include "common/geometry/linetest.h"
#include "common/geometry/line.h"
#include "common/geometry/circle.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Common::Geometry;

void LineTest::getIntersectPoints_circleWithNoIntersects_intersectPointsCountIs0()
{
	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT_EQUAL((size_t)0, line.getIntersectPoints(Circle(Point(0,0), 1)).size());
}

void LineTest::getIntersectPoints_circleToutchesLine_intersectPointsCountIs1()
{
	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT_EQUAL((size_t)1, line.getIntersectPoints(Circle(Point(0,0), 4)).size());
}

void LineTest::getIntersectPoints_circleIntersectsLine_intersectPointsCountIs2()
{
	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT_EQUAL((size_t)2, line.getIntersectPoints(Circle(Point(0,0), 5)).size());
}

void LineTest::getIntersectPoints_circleToutchesLineAt0And2_intersectPointsIs0And2()
{

	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT(Point(0,2) == line.getIntersectPoints(Circle(Point(0,0), 4)).front());
}

void LineTest::getIntersectPoints_circleIntersectsLineAtMinus1And1_intersectPointsIsMinus1And1()
{
	Compare compare(0.0001);
	Line line(Point(-2,1), Point(2,1));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(-1,1), line.getIntersectPoints(Circle(Point(0,0), 2.8284)).back()));
}

void LineTest::getIntersectPoints_circleIntersectsLineAt1And1_intersectPointsIs1And1()
{
	Compare compare(0.0001);
	Line line(Point(-2,1), Point(2,1));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1), line.getIntersectPoints(Circle(Point(0,0), 2.8284)).front()));
}

void LineTest::getIntersectPoints_circleAt1And1IntersectsLineAt2And2_intersectPointsIs2And2()
{
	Compare compare(0.0001);
	Line line(Point(-2,2), Point(3,2));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,2), line.getIntersectPoints(Circle(Point(1,1), 2.8284)).front()));
}

void LineTest::getIntersectPoints_lineIsVertical_intersectPointIsMinus1AndMinus1()
{
	Compare compare(0.0001);
	Line line(Point(-1,-2), Point(-1,3));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(-1,-1), line.getIntersectPoints(Circle(Point(0,0), 2.8284)).back()));
}

void LineTest::getIntersectPoints_lineIsVerticalAndCircleIsNotAt0And0_intersectPointIs2And2()
{
	Compare compare(0.0001);
	Line line(Point(2,0), Point(2,5));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,2), line.getIntersectPoints(Circle(Point(3,3), 2.8284)).back()));
}

void LineTest::getIntersectPoints_circleBehindEndPointWithNoIntersects_intersectPointsCountIs0()
{
	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT_EQUAL((size_t)0, line.getIntersectPoints(Circle(Point(4,2), 1)).size());
}

void LineTest::getIntersectPoints_circleOverEndPointWithNoIntersects_intersectPointsCountIs0()
{
	Line line(Point(3,0), Point(4,1));

	CPPUNIT_ASSERT_EQUAL((size_t)0, line.getIntersectPoints(Circle(Point(4,3.1), 2)).size());
}

void LineTest::getIntersectPoints_circleIntersectsLineButOnlyTheSmallerPointIsOnTheLine_intersectPointsCountIs2()
{
	Line line(Point(-2,2), Point(0,2));

	CPPUNIT_ASSERT_EQUAL((size_t)2, line.getIntersectPoints(Circle(Point(0,0), 5)).size());
}

void LineTest::getIntersectPoints_circleIntersectsLineButOnlyTheHigherPointIsOnTheLine_intersectPointsCountIs2()
{
	Line line(Point(0,2), Point(2,2));

	CPPUNIT_ASSERT_EQUAL((size_t)2, line.getIntersectPoints(Circle(Point(0,0), 5)).size());
}

void LineTest::isTargetPointRightOfLine_rightOfLine_true()
{
	Line line(Point(1, 2), Point(1, 1.5));
	Point target(-5, -10);

	CPPUNIT_ASSERT(line.isTargetPointRightOfLine(target));
}

void LineTest::isTargetPointRightOfLine_leftOfLine_false()
{
	Line line(Point(1, 2), Point(1, 1.5));
	Point target(5, 10);

	CPPUNIT_ASSERT(!line.isTargetPointRightOfLine(target));
}

void LineTest::getPerpendicularPoint_pointIs1And2_resultIsCorrect()
{
	Line line(Point(1, 1), Point(3, 3));
	Point target(1, 2);

	CPPUNIT_ASSERT_EQUAL(Point(1.5,1.5), line.getPerpendicularPoint(target));
}

void LineTest::getPerpendicularPoint_pointIs1p5And2_resultIsCorrect()
{
	Line line(Point(0, 0), Point(3, 1.5));
	Point target(1.5, 2);

	CPPUNIT_ASSERT_EQUAL(Point(2,1), line.getPerpendicularPoint(target));
}

void LineTest::isOnePointLeftAndOneRightOfLine_strangeExample_resultIsTrue()
{
	Line line(Point(3,-1.36), Point(5,0));
	Point targetLeft(3.76,-1.12);
	Point targetRight(2.5,1.12);

	CPPUNIT_ASSERT(line.isOnePointLeftAndOneRightOfLine(targetLeft, targetRight));
}

void LineTest::shiftParallel_shiftLine_resultIsCorrect()
{
	Line line(Point(0,0), Point(3,1));
	line.shiftParallel(Point(2,2));

	CPPUNIT_ASSERT_EQUAL(Point(2,2), line.getStart());
	CPPUNIT_ASSERT_EQUAL(Point(5,3), line.getEnd());
}

void LineTest::getPointOnDirectionOfLine_percentOfLenghtOfLineIs0_resultIsStart()
{
	Line line(Point(1,1), Point(3,1));

	CPPUNIT_ASSERT_EQUAL(Point(1,1),line.getPointOnDirectionOfLine(0));
}

void LineTest::getPointOnDirectionOfLine_percentOfLenghtOfLineIs1_resultIsEnd()
{
	Line line(Point(1,1), Point(3,1));

	CPPUNIT_ASSERT_EQUAL(Point(3,1),line.getPointOnDirectionOfLine(1));
}

void LineTest::getPointOnDirectionOfLine_percentOfLenghtOfLineIs2_resultIsCorrect()
{
	Line line(Point(1,1), Point(2,2));

	CPPUNIT_ASSERT_EQUAL(Point(3,3),line.getPointOnDirectionOfLine(2));
}

void LineTest::getIntersectPoint_linesAreParralel_noIntersect()
{
	Line lineOne(Point(0,0), Point(1,0));
	Line lineTwo(Point(0,1), Point(1,1));

	CPPUNIT_ASSERT(lineOne.getIntersectPoint(lineTwo).empty());
}

void LineTest::getIntersectPoint_linesAreVerticalButNotToutching_noIntersect()
{
	Line lineOne(Point(0,0), Point(2,0));
	Line lineTwo(Point(1,1), Point(1,2));

	CPPUNIT_ASSERT(lineOne.getIntersectPoint(lineTwo).empty());
}

void LineTest::getIntersectPoint_linesAreVerticalAndIntersecting_oneIntersect()
{
	Line lineOne(Point(0,0), Point(2,0));
	Line lineTwo(Point(1,-1), Point(1,1));

	CPPUNIT_ASSERT_EQUAL(Point(1,0),lineOne.getIntersectPoint(lineTwo).front());
}

void LineTest::getIntersectPoint_linesAreIntersecting_oneIntersect()
{
	Line lineOne(Point(-1,-1), Point(1,1));
	Line lineTwo(Point(-1,1), Point(1,-1));

	CPPUNIT_ASSERT_EQUAL(Point(0,0),lineOne.getIntersectPoint(lineTwo).front());
}

void LineTest::getIntersectPoint_linesAreToutching_oneIntersect()
{
	Line lineOne(Point(-1,-1), Point(1,1));
	Line lineTwo(Point(-1,1), Point(0,0));

	CPPUNIT_ASSERT_EQUAL(Point(0,0),lineOne.getIntersectPoint(lineTwo).front());
}
