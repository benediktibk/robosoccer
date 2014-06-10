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
	Point target(0,0);

	CPPUNIT_ASSERT(!straight.isTargetPointRightOfLine(target));
}

void StraightTest::isTargetPointRightOfLine_straightIsNegativeXAxisAndPointIsRightOfXAxis_true()
{
	Straight straight(Point::zero(), Angle::getQuarterRotation() * 3.0);
	Point target(1,1);

	CPPUNIT_ASSERT(!straight.isTargetPointRightOfLine(target));
}
