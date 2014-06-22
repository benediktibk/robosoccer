#include "common/geometry/straighttest.h"
#include "common/geometry/straight.h"
#include "common/geometry/line.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Common::Geometry;

void StraightTest::isTargetPointRightOfLine_straightIsXAxisAndPointIsRight_true()
{
	Straight straight(Point::zero(), Angle());
	Point target(1.2, -0.6);

	CPPUNIT_ASSERT(straight.isTargetPointRightOfLine(target));
}

void StraightTest::isTargetPointRightOfLine_straightIsYAxisAndPointIsLeft_false()
{
	Straight straight(Point::zero(), Angle::getQuarterRotation());
	Point target(-2.7, 5.6);

	CPPUNIT_ASSERT(!straight.isTargetPointRightOfLine(target));
}

void StraightTest::isTargetPointRightOfLine_straightAndPointIsRight_true()
{
	Straight straight(Point(1,2.1), Angle::getEighthRotation() * 3.0);
	Point target(4,5);

	CPPUNIT_ASSERT(straight.isTargetPointRightOfLine(target));
}

void StraightTest::isTargetPointRightOfLine_straightIsNegativeXAxisAndPointIsRightOfXAxis_false()
{
	Straight straight(Point::zero(), Angle::getQuarterRotation() * 3.0);
	Point target(1,1);

	CPPUNIT_ASSERT(!straight.isTargetPointRightOfLine(target));
}

void StraightTest::isTargetPointRightOfLine_straightThroughOriginPointIsRight_true()
{
	Straight straight(Point::zero(), Angle::getEighthRotation());
	Point target(0.1,0);

	CPPUNIT_ASSERT(straight.isTargetPointRightOfLine(target));
}

void StraightTest::getIntersectPoint_straightsAreParralel_noIntersect()
{
	Straight straightOne(Point(0,0), Angle());
	Straight straightTwo(Point(0,1), Angle());

	CPPUNIT_ASSERT(straightOne.getIntersectPoint(straightTwo).empty());
}

void StraightTest::getIntersectPoint_straightsAreIntersecting_oneIntersect()
{
	Straight straightOne(Point(-1,-1), Angle::getEighthRotation());
	Straight straightTwo(Point(2,0), Angle());

	CPPUNIT_ASSERT_EQUAL(Point(0,0), straightOne.getIntersectPoint(straightTwo).front());
}

void StraightTest::getIntersectPoint_straightsAreEqual_noIntersect()
{
	Straight straightOne(Point(1,0), Angle());
	Straight straightTwo(Point(2,0), Angle());

	CPPUNIT_ASSERT(straightOne.getIntersectPoint(straightTwo).empty());
}

void StraightTest::getIntersectPoint_straightAndLineAreParralel_noIntersect()
{
	Straight straight(Point(0,0), Angle());
	Line line(Point(0,1), Point(0,2));

	CPPUNIT_ASSERT(straight.getIntersectPoint(line).empty());
}

void StraightTest::getIntersectPoint_straightAndLineAreIntersecting_oneIntersect()
{
	Straight straight(Point(0,0), Angle());
	Line line(Point(0,3), Point(0,-1));

	CPPUNIT_ASSERT_EQUAL(Point(0,0), straight.getIntersectPoint(line).front());
}

void StraightTest::getIntersectPoint_straightAndLineAreNotIntersecting_noIntersect()
{
	Straight straight(Point(0,0), Angle());
	Line line(Point(0,3), Point(0,1));

	CPPUNIT_ASSERT(straight.getIntersectPoint(line).empty());
}

void StraightTest::shiftParallel_shiftStraight_resultIsCorrect()
{
	Straight straight(Point(0,0), Angle::getQuarterRotation());
	straight.shiftParallel(Point(2,2));

	CPPUNIT_ASSERT_EQUAL(Point(1,Angle::getQuarterRotation()), straight.getNormalizedDirectionVector());
	CPPUNIT_ASSERT_EQUAL(Point(2,2), straight.getReferencePoint());
}

void StraightTest::getPerpendicularPoint_pointOnLine_samePoint()
{
	Straight straight(Point(1, 1), Angle::getEighthRotation());
	Point point(3, 3);

	Point result = straight.getPerpendicularPoint(point);

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(point, result));
}

void StraightTest::getPerpendicularPoint_pointLeftOfLine_resultIsCorrect()
{
	Straight straight(Point(0, 1), Angle::getEighthRotation());
	Point point(2, 1);

	Point result = straight.getPerpendicularPoint(point);

	Compare compare(0.0001);
	Point resultShouldBe(1, 2);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(resultShouldBe, result));
}

void StraightTest::getPerpendicularPoint_pointRightOfLine_resultIsCorrect()
{
	Straight straight(Point(0, 1), Angle::getEighthRotation());
	Point point(0, 3);

	Point result = straight.getPerpendicularPoint(point);

	Compare compare(0.0001);
	Point resultShouldBe(1, 2);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(resultShouldBe, result));
}
