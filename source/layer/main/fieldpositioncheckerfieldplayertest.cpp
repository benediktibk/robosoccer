#include "layer/main/fieldpositioncheckerfieldplayertest.h"
#include "layer/main/fieldpositioncheckerfieldplayer.h"
#include "common/geometry/point.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Common::Geometry;

void FieldPositionCheckerFieldPlayerTest::isPointInsideField_notInsideField_false()
{
	FieldPositionCheckerFieldPlayer fieldPositionChecker;

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideField(Point(-2, 5)));
}

void FieldPositionCheckerFieldPlayerTest::isPointInsideField_onFieldNotInGoalZone_true()
{
	FieldPositionCheckerFieldPlayer fieldPositionChecker;

	CPPUNIT_ASSERT(fieldPositionChecker.isPointInsideField(Point(0.5, -0.3)));
}

void FieldPositionCheckerFieldPlayerTest::isPointInsideField_onFieldAndInGoalZone_false()
{
	FieldPositionCheckerFieldPlayer fieldPositionChecker;

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideField(Point(1.3, 0.2)));
}

void FieldPositionCheckerFieldPlayerTest::isPointInsideField_1cmDistanceToSideEdge_false()
{
	FieldPositionCheckerFieldPlayer fieldPositionChecker;

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideField(Point(0, 0.89)));
}

void FieldPositionCheckerFieldPlayerTest::isPointInsideField_6cmDistanceToSideEdge_true()
{
	FieldPositionCheckerFieldPlayer fieldPositionChecker;

	CPPUNIT_ASSERT(fieldPositionChecker.isPointInsideField(Point(0, 0.84)));
}
