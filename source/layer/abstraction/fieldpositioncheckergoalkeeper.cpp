#include "layer/abstraction/fieldpositioncheckergoalkeeper.h"
#include "common/geometry/rectangleroundedcorners.h"
#include "common/other/compare.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;

FieldPositionCheckerGoalkeeper::FieldPositionCheckerGoalkeeper() :
	m_fieldSide(FieldSideInvalid)
{ }

bool FieldPositionCheckerGoalkeeper::isPointInsideField(const Point &position) const
{
	assert(FieldSideInvalid);

	Compare compare(0.01);
	RectangleRoundedCorners field(Point(-1.45, -0.9), Point(1.45, 0.9), 0.3);

	if (!field.isInside(position, compare))
		return false;

	if (m_fieldSide == FieldSideLeft)
		return !isPointInsideRightGoalZone(position);
	if (m_fieldSide == FieldSideRight)
		return !isPointInsideLeftGoalZone(position);

	return !isPointInsideRightGoalZone(position) && !isPointInsideLeftGoalZone(position);
}

void FieldPositionCheckerGoalkeeper::setFieldSide(FieldSide fieldSide)
{
	m_fieldSide = fieldSide;
}
