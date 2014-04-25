#include "layer/main/targetpositionfetcher.h"
#include "common/geometry/orientedposition.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

TargetPositionFetcher::TargetPositionFetcher() :
	m_fieldside(FieldSideInvalid)
{ }

void TargetPositionFetcher::setFieldSide(FieldSide fieldside)
{
	m_fieldside = fieldside;
}

OrientedPosition TargetPositionFetcher::getStartPosition() const
{
	assert(m_fieldside != FieldSideInvalid);

	return OrientedPosition();
}

OrientedPosition TargetPositionFetcher::getGoalPosition() const
{
	assert(m_fieldside != FieldSideInvalid);

	OrientedPosition goalposition;
	switch (m_fieldside)
	{
	case FieldSideInvalid:
	case FieldSideRight:
		goalposition = OrientedPosition(Point(1.45,0),Angle());
		break;
	case FieldSideLeft:
		goalposition = OrientedPosition(Point(-1.45,0),Angle::getHalfRotation());
		break;
	}
	return goalposition;
}

