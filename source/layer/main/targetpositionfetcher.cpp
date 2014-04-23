#include "layer/main/targetpositionfetcher.h"
#include "common/geometry/orientedposition.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Common::Geometry;

TargetPositionFetcher::TargetPositionFetcher() :
	m_fieldside(Layer::Abstraction::FieldSideInvalid)
{ }

void TargetPositionFetcher::setFieldSide(Abstraction::FieldSide fieldside)
{
	m_fieldside = fieldside;
}

OrientedPosition TargetPositionFetcher::getStartPosition() const
{
	return OrientedPosition();
}

