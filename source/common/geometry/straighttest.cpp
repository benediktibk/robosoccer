#include "common/geometry/straighttest.h"
#include "common/geometry/straight.h"

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

void StraightTest::getIntersectPoint_linesAreParralel_noIntersect()
{
	Straight straightOne(Point(0,0), Angle());
	Straight straightTwo(Point(0,1), Angle());

	CPPUNIT_ASSERT(straightOne.getIntersectPoint(straightTwo).empty());
}

void StraightTest::getIntersectPoint_linesAreIntersecting_oneIntersect()
{
	Straight straightOne(Point(-1,-1), Angle::getEighthRotation());
	Straight straightTwo(Point(2,0), Angle());

	CPPUNIT_ASSERT_EQUAL(Point(0,0), straightOne.getIntersectPoint(straightTwo).front());
}

void StraightTest::getIntersectPoint_linesAreToutching_oneIntersect()
{
	Straight straightOne(Point(1,0), Angle());
	Straight straightTwo(Point(2,0), Angle());

	CPPUNIT_ASSERT_EQUAL(Point(0,0), straightOne.getIntersectPoint(straightTwo).front());
}
