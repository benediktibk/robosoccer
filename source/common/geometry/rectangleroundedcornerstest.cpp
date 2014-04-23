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

void RectangleRoundedCornersTest::isInside_isInsideRoundCorner_true()
{
	Compare compare(0.001);
	RectangleRoundedCorners rect(Point(0,0), Point(10,10), 2.0);

	CPPUNIT_ASSERT(rect.isInside(Point(1,1), compare));
}
