#include "layer/abstraction/fieldpositioncheckertest.h"
#include "layer/abstraction/fieldpositioncheckermock.h"
#include "common/geometry/point.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

void FieldPositionCheckerTest::isPointInsideGoalZone_atFrontEdgeOfLeftGoal_false()
{
	FieldPositionCheckerMock fieldPositionChecker;

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideGoalZone(Point(-1.45 + 0.25, 0)));
}

void FieldPositionCheckerTest::isPointInsideGoalZone_atLeftEdgeOfLeftGoal_false()
{
	FieldPositionCheckerMock fieldPositionChecker;

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideGoalZone(Point(-1.45 + 0.25/2, 0.35)));
}

void FieldPositionCheckerTest::isPointInsideGoalZone_atRightEdgeOfLeftGoal_false()
{
	FieldPositionCheckerMock fieldPositionChecker;

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideGoalZone(Point(-1.45 + 0.25/2, -0.35)));
}

void FieldPositionCheckerTest::isPointInsideGoalZone_atFrontEdgeOfRightGoal_false()
{
	FieldPositionCheckerMock fieldPositionChecker;

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideGoalZone(Point(1.45 - 0.25, 0)));
}

void FieldPositionCheckerTest::isPointInsideGoalZone_atLeftEdgeOfRightGoal_false()
{
	FieldPositionCheckerMock fieldPositionChecker;

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideGoalZone(Point(1.45 - 0.25/2, -0.35)));
}

void FieldPositionCheckerTest::isPointInsideGoalZone_atRightEdgeOfRightGoal_false()
{
	FieldPositionCheckerMock fieldPositionChecker;

	CPPUNIT_ASSERT(!fieldPositionChecker.isPointInsideGoalZone(Point(1.45 - 0.25/2, 0.35)));
}

void FieldPositionCheckerTest::isPointInsideGoalZone_inMiddleOfLeftGoalZone_true()
{
	FieldPositionCheckerMock fieldPositionChecker;

	CPPUNIT_ASSERT(fieldPositionChecker.isPointInsideGoalZone(Point(-1.45 + 0.25/2, 0)));
}

void FieldPositionCheckerTest::isPointInsideGoalZone_inMiddleOfRightGoalZone_true()
{
	FieldPositionCheckerMock fieldPositionChecker;

	CPPUNIT_ASSERT(fieldPositionChecker.isPointInsideGoalZone(Point(1.45 - 0.25/2, 0)));
}
