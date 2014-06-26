#include "layer/abstraction/fieldpositioncheckergoalkeeper.h"
#include "common/geometry/rectangleroundedcorners.h"
#include "common/geometry/rectangle.h"
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

bool FieldPositionCheckerGoalkeeper::isPointInsideDangerZone(const Common::Geometry::Point &ballPosition) const
{
	assert(m_fieldSide != FieldSideInvalid);

	Compare compare(0.005);
	Rectangle dangerZone;

	if(m_fieldSide == FieldSideLeft)
		dangerZone = Rectangle(Point(-1.65,0.2),Point(-1.39,-0.2));
	else
		dangerZone = Rectangle(Point(1.39,0.2),Point(1.65,-0.2));
	return dangerZone.isInside(ballPosition,compare);
}

void FieldPositionCheckerGoalkeeper::setFieldSide(FieldSide fieldSide)
{
	m_fieldSide = fieldSide;
}


