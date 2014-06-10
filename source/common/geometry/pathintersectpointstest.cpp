#include "common/geometry/pathintersectpointstest.h"
#include "common/geometry/pathintersectpoints.h"

using namespace RoboSoccer::Common::Geometry;
using namespace std;

void PathIntersectPointsTest::constructor_createDefaultObject_intersectPointsCountIs2()
{
	vector<Point> intersectPoints;
	intersectPoints.push_back(Point(0,0));
	intersectPoints.push_back(Point(1,1));
	PathIntersectPoints pathIntersectPoints(intersectPoints, PathIntersectPoints::IntersectTypeFromLeft);

	CPPUNIT_ASSERT_EQUAL((size_t)2, pathIntersectPoints.getCount());
}

void PathIntersectPointsTest::constructor_createDefaultObject_intersectTypeFromLeft()
{
	vector<Point> intersectPoints;
	intersectPoints.push_back(Point(0,0));
	intersectPoints.push_back(Point(1,1));
	PathIntersectPoints pathIntersectPoints(intersectPoints, PathIntersectPoints::IntersectTypeFromLeft);

	CPPUNIT_ASSERT_EQUAL(PathIntersectPoints::IntersectTypeFromLeft, pathIntersectPoints.getIntersectTypeFrom());
}
