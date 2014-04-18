#include "common/routing/routelengthcomparetest.h"
#include "common/routing/routelengthcompare.h"
#include "common/routing/route.h"

using namespace RoboSoccer::Common::Routing;
using namespace RoboSoccer::Common::Geometry;

void RouteLengthCompareTest::evaluation_firstOneShorter_true()
{
	RouteLengthCompare compare;
	Route one(0.1);
	one.addPoint(Point(0, 0));
	one.addPoint(Point(0, 1));
	one.addPoint(Point(2, 2));
	Route two(0.1);
	two.addPoint(Point(-1, 2));
	two.addPoint(Point(10, 10));

	CPPUNIT_ASSERT(compare(one, two));
}

void RouteLengthCompareTest::evaulation_secondOneShorter_false()
{
	RouteLengthCompare compare;
	Route one(0.1);
	one.addPoint(Point(0, 0));
	one.addPoint(Point(0, 1));
	one.addPoint(Point(2, 2));
	Route two(0.1);
	two.addPoint(Point(-1, 2));
	two.addPoint(Point(-2, 3));

	CPPUNIT_ASSERT(!compare(one, two));
}
