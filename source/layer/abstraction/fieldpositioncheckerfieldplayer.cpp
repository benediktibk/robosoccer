#include "layer/abstraction/fieldpositioncheckerfieldplayer.h"
#include "common/geometry/rectangleroundedcorners.h"
#include "common/other/compare.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;

bool FieldPositionCheckerFieldPlayer::isPointInsideField(const Point &position) const
{
	Compare compare(0.005);
	RectangleRoundedCorners field(Point(-1.42, -0.87), Point(1.42, 0.87), 0.3);

	if (!field.isInside(position, compare))
		return false;

	return !isPointInsideLeftGoalZone(position) && !isPointInsideRightGoalZone(position);
}
