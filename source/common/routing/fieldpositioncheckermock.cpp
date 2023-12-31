#include "common/routing/fieldpositioncheckermock.h"
#include "common/geometry/point.h"

using namespace RoboSoccer::Common::Routing;

FieldPositionCheckerMock::FieldPositionCheckerMock() :
	m_negativeCoordinatesOutside(false),
	m_allPointsOutside(false)
{ }

bool FieldPositionCheckerMock::isPointInsideField(Geometry::Point const &position) const
{
	if (m_allPointsOutside)
		return false;
	else if (m_negativeCoordinatesOutside)
	{
		if (position.getX() < 0 || position.getY() < 0)
			return false;
		else
			 return true;
	}
	else
		return true;
}

void FieldPositionCheckerMock::setNegativeCoordinatesOutside(bool value)
{
	m_negativeCoordinatesOutside = value;
}

void FieldPositionCheckerMock::setAllCoordinatesOutside(bool value)
{
	m_allPointsOutside = value;
}
