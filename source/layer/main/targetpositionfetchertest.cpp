#include "layer/main/targetpositionfetchertest.h"
#include "layer/main/targetpositionfetcher.h"
#include "common/geometry/orientedposition.h"
#include "layer/abstraction/fieldside.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Abstraction;

void TargetPositionFetcherTest::getGoalPosition_fieldSideRight_correctPosition()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);

	CPPUNIT_ASSERT(OrientedPosition(Point(1.45,0),Angle()) == targetPositionFetcher.getGoalPosition());
}
