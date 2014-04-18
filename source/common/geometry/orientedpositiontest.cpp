#include "common/geometry/orientedpositiontest.h"
#include "common/geometry/orientedposition.h"
#include "common/geometry/compare.h"
#include <sstream>
#include <math.h>

using namespace RoboSoccer::Common::Geometry;
using namespace std;

void OrientedPositionTest::constructor_empty_positionIs0And0()
{
	OrientedPosition position;

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0, 0), position.getPosition()));
}

void OrientedPositionTest::constructor_4And3_positionIs4And3()
{
	OrientedPosition position(Point(4, 3), 0);

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(4, 3), position.getPosition()));
}

void OrientedPositionTest::setPosition_5And6_positionIs5And6()
{
	OrientedPosition position;

	position.setPosition(Point(5, 6));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 6), position.getPosition()));
}

void OrientedPositionTest::streamOperator_3And2_32()
{
	OrientedPosition position(Point(3, 2), 1);
	stringstream stream;

	stream << position;

	CPPUNIT_ASSERT_EQUAL(string("(3, 2, 1)"), stream.str());
}

void OrientedPositionTest::operatorMultiply_3And6With2_6And12()
{
	OrientedPosition position(Point(3, 6), Angle(-2));

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(OrientedPosition(Point(6, 12), Angle(-2)), position*2));
}

void OrientedPositionTest::operatorDivide_3And6With3_1And2()
{
	OrientedPosition position(Point(3, 6), Angle(1));

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(OrientedPosition(Point(1, 2), Angle(1)), position/3));
}

void OrientedPositionTest::operatorAdd_4And3To5And1_9And4()
{
	OrientedPosition positionOne(Point(4, 3), -2);
	OrientedPosition positionTwo(Point(5, 1), 1);

	OrientedPosition result = positionOne + positionTwo;

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(OrientedPosition(Point(9, 4), 0), result));
}

void OrientedPositionTest::operatorMinus_5And3From9And4_4And1()
{
	OrientedPosition positionOne(Point(9, 4), Angle(1));
	OrientedPosition positionTwo(Point(5, 3), Angle(-2));

	OrientedPosition result = positionOne - positionTwo;

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(OrientedPosition(Point(4, 1), 0), result));
}

void OrientedPositionTest::operatorMultpliyAndAssign_3And5With2_6And10()
{
	OrientedPosition position(Point(3, 5), 2);

	position *= 2;

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(OrientedPosition(Point(6, 10), 2), position));
}

void OrientedPositionTest::distanceTo_from4And5To8And2_5()
{
	OrientedPosition one(Point(4, 5), Angle(3));
	OrientedPosition two(Point(8, 2), Angle(-1));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, one.distanceTo(two), 0.00001);
}

void OrientedPositionTest::constructor_empty_orientationIs0()
{
	OrientedPosition position;

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(0), position.getOrientation()));
}


void OrientedPositionTest::setOrientation_3_orientationIs3()
{
	OrientedPosition position;

	position.setOrientation(Angle(3));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(3), position.getOrientation()));
}

void OrientedPositionTest::read_validString_correctValues()
{
	OrientedPosition source(Point(1.3, 3.2), Angle(1.1));
	OrientedPosition destination;
	stringstream stream;
	stream << source;
	string sourceString = stream.str();

	destination.read(sourceString);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.3, destination.getPosition().getX(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.2, destination.getPosition().getY(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.1, destination.getOrientation().getValueBetweenMinusPiAndPi(), 0.0001);
}

void OrientedPositionTest::getRelativeOrientationTo_lookingUpAndTargetInFourthQuarter_correctValue()
{
	OrientedPosition source(Point(1, 2), Angle::getQuarterRotation());
	Point point(2, 1);

	Angle result = source.getRelativeOrientationTo(point);

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getEighthRotation()*(-3), result));
}

void OrientedPositionTest::constructor_orientationIsPi_orientationIsPi()
{
	OrientedPosition position(Point(10, 23), Angle(M_PI));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(M_PI), position.getOrientation()));
}
