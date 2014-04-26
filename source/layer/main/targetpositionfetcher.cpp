#include "layer/main/targetpositionfetcher.h"
#include "common/geometry/orientedposition.h"
#include "layer/abstraction/ball.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

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

vector<OrientedPosition> TargetPositionFetcher::getEnemyGoalPosition() const
{
	vector<OrientedPosition> goalposition;
	goalposition.reserve(3);

	switch (m_fieldside)
	{
	case FieldSideInvalid:
		assert(false);
	case FieldSideRight:
		goalposition.push_back(OrientedPosition(Point(1.45,0),Angle()));
		goalposition.push_back(OrientedPosition(Point(1.45,-0.2),Angle()));
		goalposition.push_back(OrientedPosition(Point(1.45,0.2),Angle()));
		break;
	case FieldSideLeft:
		goalposition.push_back(OrientedPosition(Point(-1.45,0),Angle::getHalfRotation()));
		goalposition.push_back(OrientedPosition(Point(-1.45,0.2),Angle::getHalfRotation()));
		goalposition.push_back(OrientedPosition(Point(-1.45,-0.2),Angle::getHalfRotation()));
		break;
	}
	return goalposition;
}

OrientedPosition TargetPositionFetcher::getOwnGoalPosition(const Ball &ball) const
{
	OrientedPosition goalPosition;

	switch (m_fieldside)
	{
	case FieldSideInvalid:
		assert(false);
	case FieldSideRight:
		goalPosition = OrientedPosition(Point(1.3,ball.getPosition().getPosition().getY()),Angle::getHalfRotation());
		break;
	case FieldSideLeft:
		goalPosition = OrientedPosition(Point(-1.3,ball.getPosition().getPosition().getY()),Angle());
		break;
	}

	return goalPosition;
}

OrientedPosition TargetPositionFetcher::getPenaltyPositionKicker() const
{
	assert(m_fieldside != FieldSideInvalid);

	return OrientedPosition();
}

