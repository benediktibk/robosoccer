#include "common/geometry/comparetest.h"
#include "common/geometry/compare.h"
#include "common/geometry/angle.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Common::Geometry;
using namespace std;

void CompareTest::isFuzzyEqual_twoNearlyEqualVectorsWithExtraAgnleCompare_true()
{
	Compare compare(0.1);
	vector<Pose> vector1, vector2;
	vector1.push_back(Pose(Point(1, 1.05), Angle(0.05)));
	vector1.push_back(Pose(Point(1, 3), Angle::getEighthRotation()));
	vector2.push_back(Pose(Point(1, 1), Angle()));
	vector2.push_back(Pose(Point(1, 3), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(compare.isFuzzyEqualWithCorrectOrder(vector1, vector2, 0.05));
}

void CompareTest::isFuzzyEqual_twoNearlyEqualVectorsWithExtraAgnleCompareAndAngleCompareToSmall_false()
{
	Compare compare(0.1);
	vector<Pose> vector1, vector2;
	vector1.push_back(Pose(Point(1, 1.05), Angle(0.05)));
	vector1.push_back(Pose(Point(1, 3), Angle::getEighthRotation()));
	vector2.push_back(Pose(Point(1, 1), Angle()));
	vector2.push_back(Pose(Point(1, 3), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(!compare.isFuzzyEqualWithCorrectOrder(vector1, vector2, 0.01));
}

void CompareTest::isFuzzyEqual_twoCompletelyEqualVectors_true()
{
	Compare compare(0.001);
	vector<Pose> vector1, vector2;
	vector1.push_back(Pose(Point(1, 1), Angle()));
	vector1.push_back(Pose(Point(1, 3), Angle::getEighthRotation()));
	vector2.push_back(Pose(Point(1, 1), Angle()));
	vector2.push_back(Pose(Point(1, 3), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(compare.isFuzzyEqualWithCorrectOrder(vector1, vector2));
}

void CompareTest::isFuzzyEqual_twoNearlyEqualVectors_true()
{
	Compare compare(0.1);
	vector<Pose> vector1, vector2;
	vector1.push_back(Pose(Point(1, 1.05), Angle(0.1)));
	vector1.push_back(Pose(Point(1, 3), Angle::getEighthRotation()));
	vector2.push_back(Pose(Point(1, 1), Angle()));
	vector2.push_back(Pose(Point(1, 3), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(compare.isFuzzyEqualWithCorrectOrder(vector1, vector2));
}

void CompareTest::isFuzzyEqual_twoVectorsWithDifferentSize_false()
{
	Compare compare(0.1);
	vector<Pose> vector1, vector2;
	vector1.push_back(Pose(Point(1, 1), Angle()));
	vector1.push_back(Pose(Point(1, 3), Angle::getEighthRotation()));
	vector1.push_back(Pose(Point(1, 2), Angle::getEighthRotation()));
	vector2.push_back(Pose(Point(1, 1), Angle()));
	vector2.push_back(Pose(Point(1, 3), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(!compare.isFuzzyEqualWithCorrectOrder(vector1, vector2));
}

void CompareTest::isFuzzyEqual_towVectorsWithOrientedPositions_true()
{
	Compare compare(0.1);
	vector<Pose> vector1, vector2;
	vector1.push_back(Pose(Point(1, 2), Angle::getEighthRotation()));
	vector1.push_back(Pose(Point(1, 2.5), Angle::getEighthRotation()));
	vector2.push_back(Pose(Point(1, 2), Angle::getEighthRotation()));
	vector2.push_back(Pose(Point(1, 2.5), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(compare.isFuzzyEqualWithCorrectOrder(vector1, vector2));
}

void CompareTest::isFuzzyEqual_twoDifferentVectorsWithOrientedPositions_false()
{
	Compare compare(0.1);
	vector<Pose> vector1, vector2;
	vector1.push_back(Pose(Point(1, 2), Angle::getEighthRotation()));
	vector1.push_back(Pose(Point(1, 2.5), Angle::getEighthRotation()));
	vector2.push_back(Pose(Point(1, 3), Angle::getEighthRotation()));
	vector2.push_back(Pose(Point(1, 2.5), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(!compare.isFuzzyEqualWithCorrectOrder(vector1, vector2));
}

void CompareTest::isFuzzyEqual_towVectorsWithOrientedPositionsInDiffrentOrder_false()
{
	Compare compare(0.1);
	vector<Pose> vector1, vector2;
	vector1.push_back(Pose(Point(1, 2), Angle::getEighthRotation()));
	vector1.push_back(Pose(Point(1, 2.5), Angle::getEighthRotation()));
	vector2.push_back(Pose(Point(1, 2.5), Angle::getEighthRotation()));
	vector2.push_back(Pose(Point(1, 2), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(!compare.isFuzzyEqualWithCorrectOrder(vector1, vector2));
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

void CompareTest::isFuzzyEqual_twoEqualCircles_true()
{
	Compare compare(0.1);
	Circle one(Point(4, 3), 5);
	Circle two(Point(4, 3), 5);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoCirclesWithDifferentCenter_false()
{
	Compare compare(0.1);
	Circle one(Point(4, 3), 5);
	Circle two(Point(4, 8), 5);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoCirclesWithDifferentDiameter_false()
{
	Compare compare(0.1);
	Circle one(Point(4, 3), 5);
	Circle two(Point(4, 3), 1);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(one, two));
}
