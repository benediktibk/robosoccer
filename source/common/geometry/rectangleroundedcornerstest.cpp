#include "common/geometry/rectangleroundedcornerstest.h"
#include "common/geometry/rectangleroundedcorners.h"
#include "common/other/compare.h"

using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;

void RectangleRoundedCornersTest::isInside_isOutsideRoundedRectButInsideRect_false()
{
	Compare compare(0.001);
	RectangleRoundedCorners rect(Point(0,0), Point(10,10), 2.0);

	CPPUNIT_ASSERT(!rect.isInside(Point(0,0), compare));
}

void RectangleRoundedCornersTest::isInside_isInsideRect_true()
{
	Compare compare(0.001);
	RectangleRoundedCorners rect(Point(0,0), Point(10,10), 2.0);

	CPPUNIT_ASSERT(rect.isInside(Point(5,5), compare));
}

void RectangleRoundedCornersTest::isInside_isInsideRoundCornerLL_true()
{
	Compare compare(0.001);
	RectangleRoundedCorners rect(Point(0,0), Point(10,10), 2.0);

	CPPUNIT_ASSERT(rect.isInside(Point(1,1), compare));
}

void RectangleRoundedCornersTest::isInside_isInsideRoundCornerLU_true()
{
	Compare compare(0.001);
	RectangleRoundedCorners rect(Point(0,0), Point(10,10), 2.0);

	CPPUNIT_ASSERT(rect.isInside(Point(1,9), compare));
}

void RectangleRoundedCornersTest::isInside_isInsideRoundCornerRL_true()
{
	Compare compare(0.001);
	RectangleRoundedCorners rect(Point(0,0), Point(10,10), 2.0);

	CPPUNIT_ASSERT(rect.isInside(Point(9,1), compare));
}

void RectangleRoundedCornersTest::isInside_isInsideRoundCornerRU_true()
{
	Compare compare(0.001);
	RectangleRoundedCorners rect(Point(0,0), Point(10,10), 2.0);

	CPPUNIT_ASSERT(rect.isInside(Point(9,9), compare));
}
