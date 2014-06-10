#include "layer/main/fieldpositioncheckerfieldplayer.h"
#include "common/geometry/rectangleroundedcorners.h"
#include "common/other/compare.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;

FieldPositionCheckerFieldPlayer::FieldPositionCheckerFieldPlayer()
{ }

bool FieldPositionCheckerFieldPlayer::isPointInsideField(const Point &position) const
{
	Compare compare(0.005);
	RectangleRoundedCorners field(Point(-1.4, -0.85), Point(1.4, 0.85), 0.3);

	if (!field.isInside(position, compare))
		return false;

	return !isPointInsideLeftGoalZone(position) && !isPointInsideRightGoalZone(position);
}
