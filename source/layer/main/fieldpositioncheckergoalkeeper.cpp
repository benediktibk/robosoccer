#include "layer/main/fieldpositioncheckergoalkeeper.h"
#include "common/geometry/rectangleroundedcorners.h"
#include "common/other/compare.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;

bool FieldPositionCheckerGoalkeeper::isPointInsideField(const Point &position) const
{
	Compare compare(0.01);
	RectangleRoundedCorners field(Point(-1.45, -0.9), Point(1.45, 0.9), 0.3);

	if (!field.isInside(position, compare))
		return false;

	Rectangle goalZoneRight(Point(1.2, -0.35), Point(1.45, 0.35));
	Rectangle goalZoneLeft(Point(-1.45, -0.35), Point(-1.2, 0.35));

	if (true)
		return !goalZoneRight.isInside(position, compare);

	return !goalZoneLeft.isInside(position, compare);
}
