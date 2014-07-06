#include "layer/abstraction/fieldpositioncheckergoalkeepertest.h"
#include "layer/abstraction/fieldpositioncheckergoalkeeper.h"
#include "common/geometry/point.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

void FieldPositionCheckerGoalkeeperTest::isPointInsideField_pointOutsideField_false()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;
	fieldPositionChecker.setFieldSide(FieldSideRight);

	bool result = fieldPositionChecker.isPointInsideField(Point(-0.3,2));

	CPPUNIT_ASSERT(!result);
}

void FieldPositionCheckerGoalkeeperTest::isPointInsideField_rightSidePointInOwnGoalZone_true()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;
	fieldPositionChecker.setFieldSide(FieldSideRight);

	CPPUNIT_ASSERT(fieldPositionChecker.isPointInsideField(Point(1.3,-0.2)));
}

void FieldPositionCheckerGoalkeeperTest::isPointInsideField_rightSidePointInEnemyGoalZone_false()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;
	fieldPositionChecker.setFieldSide(FieldSideRight);

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideField(Point(-1.3,0.2)));
}

void FieldPositionCheckerGoalkeeperTest::isPointInsideField_leftSidePointInOwnGoalZone_true()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;
	fieldPositionChecker.setFieldSide(FieldSideLeft);

	CPPUNIT_ASSERT(fieldPositionChecker.isPointInsideField(Point(-1.3,0.1)));
}

void FieldPositionCheckerGoalkeeperTest::isPointInsideField_leftSidePointInEnemyGoalZone_false()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;
	fieldPositionChecker.setFieldSide(FieldSideLeft);

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideField(Point(1.24,-0.23)));
}

void FieldPositionCheckerGoalkeeperTest::isPointInsideField_changingSidesInGoalZone_falseThenTrue()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;
	fieldPositionChecker.setFieldSide(FieldSideRight);

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideField(Point(-1.3,0.2)));
	CPPUNIT_ASSERT(fieldPositionChecker.isPointInsideField(Point(1.3,-0.2)));

	fieldPositionChecker.setFieldSide(FieldSideLeft);

	CPPUNIT_ASSERT(fieldPositionChecker.isPointInsideField(Point(-1.3,0.2)));
	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideField(Point(1.3,-0.2)));
}

void FieldPositionCheckerGoalkeeperTest::isPointInsideDangerZone_pointCloseToLeftGoal_true()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;
	fieldPositionChecker.setFieldSide(FieldSideLeft);
	CPPUNIT_ASSERT(fieldPositionChecker.isPointInsideDangerZone(Point(-1.43,-0.1)));
}
void FieldPositionCheckerGoalkeeperTest::isPointInsideDangerZone_pointNotCloseToRightGoal_false()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;
	fieldPositionChecker.setFieldSide(FieldSideRight);
	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideDangerZone(Point(-1.43,-0.1)));
}

void FieldPositionCheckerGoalkeeperTest::isPointInsideDangerZone_pointCloseToRightGoal_true()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;
	fieldPositionChecker.setFieldSide(FieldSideRight);
	CPPUNIT_ASSERT(fieldPositionChecker.isPointInsideDangerZone(Point(1.42,0.15)));
}

void FieldPositionCheckerGoalkeeperTest::isPointInsideDangerZone_pointNotCloseToLeftGoal_false()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;
	fieldPositionChecker.setFieldSide(FieldSideLeft);
	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideDangerZone(Point(1.42,0.15)));
}

