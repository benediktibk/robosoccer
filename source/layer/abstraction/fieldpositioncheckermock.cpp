#include "layer/abstraction/fieldpositioncheckermock.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

FieldPositionCheckerMock::FieldPositionCheckerMock() :
	m_allCoordinatesOutside(false)
{ }

bool FieldPositionCheckerMock::isPointInsideField(const Point &) const
{
	if (m_allCoordinatesOutside)
		return false;

	return true;
}

void FieldPositionCheckerMock::setAllCoordinatesOutside(bool value)
{
	m_allCoordinatesOutside = value;
}
