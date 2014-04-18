#include "common/geometry/pointdistancecomparetest.h"
#include "common/geometry/pointdistancecompare.h"

using namespace RoboSoccer::Common::Geometry;

void PointDistanceCompareTest::compare_firstOneCloserThanSecondOneBecauseOfPosition_true()
{
	Point one(3, 4);
	Point two(-3, 4);
	PointDistanceCompare compare(Point(2, 4));

	CPPUNIT_ASSERT(compare(one, two));
}

void PointDistanceCompareTest::compare_seoncdOneCloserThanFirstOneBecauseOfPosition_false()
{
	Point one(3, 4);
	Point two(-3, 4);
	PointDistanceCompare compare(Point(-3, 3));

	CPPUNIT_ASSERT(!compare(one, two));
}
