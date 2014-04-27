#include "layer/main/targetpositionfetchertest.h"
#include "layer/main/targetpositionfetcher.h"
#include "common/geometry/orientedposition.h"
#include "layer/abstraction/fieldside.h"
#include "layer/abstraction/ballmock.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Abstraction;

void TargetPositionFetcherTest::getEnemyGoalPosition_fieldSideRight_middlePosotionIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);

	CPPUNIT_ASSERT_EQUAL(targetPositionFetcher.getEnemyGoalPosition().front(),OrientedPosition(Point(1.45,0),Angle()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballInTheMiddle_goalieIsAtYBallPosition()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	BallMock ball;
	ball.setBallPosition(Point(0,0));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0,0.0001);
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballOnTheSide_goalieIsAtGoalCornerPosition()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	BallMock ball;
	ball.setBallPosition(Point(0,0.5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.25,0.0001);
}

void TargetPositionFetcherTest::getPenaltyPositionKicker_ballAtCenter_robotIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	BallMock ball;
	ball.setBallPosition(Point(0,0));

	CPPUNIT_ASSERT_EQUAL(OrientedPosition(Point(-0.05,0),Angle()),targetPositionFetcher.getPenaltyPositionKicker(ball));
}
