#include "layer/main/fieldpositionchecker.h"
#include "common/geometry/rectangle.h"
#include "common/other/compare.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;

bool FieldPositionChecker::isPointInsideLeftGoalZone(const Point &position) const
{
	Compare compare(0.01);
	Rectangle goalZoneLeft(Point(-1.45, -0.35), Point(-1.2, 0.35));
	return goalZoneLeft.isInside(position, compare);
}

bool FieldPositionChecker::isPointInsideRightGoalZone(const Point &position) const
{
	Compare compare(0.01);
	Rectangle goalZoneRight(Point(1.2, -0.35), Point(1.45, 0.35));
	return goalZoneRight.isInside(position, compare);
}

bool FieldPositionChecker::isPointInsideGoalZone(const Point &position) const
{
	return isPointInsideLeftGoalZone(position) || isPointInsideRightGoalZone(position);
}