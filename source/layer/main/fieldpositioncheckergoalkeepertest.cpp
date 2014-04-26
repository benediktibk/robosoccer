#include "layer/main/fieldpositioncheckergoalkeepertest.h"
#include "layer/main/fieldpositioncheckergoalkeeper.h"
#include "common/geometry/point.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Common::Geometry;

void FieldPositionCheckerGoalkeeperTest::isPointInsideField_pointInNeutralZone_true()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;

	CPPUNIT_ASSERT(fieldPositionChecker.isPointInsideField(Point(1,-0.6)));
}

void FieldPositionCheckerGoalkeeperTest::isPointInsideField_pointOutsideField_false()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideField(Point(-0.3,2)));
}

void FieldPositionCheckerGoalkeeperTest::isPointInsideField_pointInOwnGoalZone_true()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;

	CPPUNIT_ASSERT(fieldPositionChecker.isPointInsideField(Point(1.3,-0.2)));
}

void FieldPositionCheckerGoalkeeperTest::isPointInsideField_pointInEnemyGoalZone_false()
{
	FieldPositionCheckerGoalkeeper fieldPositionChecker;

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideField(Point(-1.3,0.2)));

}
