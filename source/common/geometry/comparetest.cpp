#include "common/geometry/comparetest.h"
#include "common/geometry/compare.h"
#include "common/geometry/angle.h"
#include "common/geometry/orientedposition.h"

using namespace RoboSoccer::Common::Geometry;
using namespace std;

void CompareTest::isFuzzyEqual_towListsWithOrientedPositions_true()
{
	Compare compare(0.1);
	list<OrientedPosition> list1, list2;
	list1.push_back(OrientedPosition(Point(1, 2), Angle::getEighthRotation()));
	list1.push_back(OrientedPosition(Point(1, 2.5), Angle::getEighthRotation()));
	list2.push_back(OrientedPosition(Point(1, 2), Angle::getEighthRotation()));
	list2.push_back(OrientedPosition(Point(1, 2.5), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(list1, list2));
}

void CompareTest::isFuzzyEqual_twoListsWithOrientedPositions_false()
{
	Compare compare(0.1);
	list<OrientedPosition> list1, list2;
	list1.push_back(OrientedPosition(Point(1, 2), Angle::getEighthRotation()));
	list1.push_back(OrientedPosition(Point(1, 2.5), Angle::getEighthRotation()));
	list2.push_back(OrientedPosition(Point(1, 3), Angle::getEighthRotation()));
	list2.push_back(OrientedPosition(Point(1, 2.5), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(list1, list2));
}

void CompareTest::isFuzzyEqual_towListsWithOrientedPositionsInDiffrentOrder_true()
{
	Compare compare(0.1);
	list<OrientedPosition> list1, list2;
	list1.push_back(OrientedPosition(Point(1, 2), Angle::getEighthRotation()));
	list1.push_back(OrientedPosition(Point(1, 2.5), Angle::getEighthRotation()));
	list2.push_back(OrientedPosition(Point(1, 2.5), Angle::getEighthRotation()));
	list2.push_back(OrientedPosition(Point(1, 2), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(list1, list2));
}

void CompareTest::isFuzzyEqual_twoAnglesNearPi_true()
{
	Compare compare(0.4);
	Angle one = Angle::convertFromDegreeToRadiant(179);
	Angle two = Angle::convertFromDegreeToRadiant(181);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoAnglesNearZero_true()
{
	Compare compare(0.4);
	Angle one = Angle::convertFromDegreeToRadiant(1);
	Angle two = Angle::convertFromDegreeToRadiant(359);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoAnglesWhichAreNotEqual_false()
{
	Compare compare(0.4);
	Angle one = Angle::convertFromDegreeToRadiant(90);
	Angle two = Angle::convertFromDegreeToRadiant(270);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoAnglesWhichHave90DegreesDifference_false()
{
	Compare compare(0.4);
	Angle one = Angle::convertFromDegreeToRadiant(180);
	Angle two = Angle::convertFromDegreeToRadiant(270);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoAnglesWhichHave270DegreesDifference_false()
{
	Compare compare(0.4);
	Angle one = Angle::convertFromDegreeToRadiant(0);
	Angle two = Angle::convertFromDegreeToRadiant(270);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoAngelsNear90Degrees_true()
{
	Compare compare(0.1);
	Angle one = Angle::convertFromDegreeToRadiant(89);
	Angle two = Angle::convertFromDegreeToRadiant(90.5);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoAngelsNear270Degrees_true()
{
	Compare compare(0.1);
	Angle one = Angle::convertFromDegreeToRadiant(269);
	Angle two = Angle::convertFromDegreeToRadiant(270.5);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(one, two));
}