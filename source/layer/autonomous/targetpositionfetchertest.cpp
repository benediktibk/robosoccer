#include "layer/autonomous/targetpositionfetchertest.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "common/geometry/pose.h"
#include "layer/abstraction/fieldside.h"
#include "layer/abstraction/ballmock.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Abstraction;

void TargetPositionFetcherTest::getEnemyGoalPosition_bothSides_middlePosotionIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	Point rightSide(targetPositionFetcher.getEnemyGoalPosition().front());
	targetPositionFetcher.setFieldSide(FieldSideLeft);

	CPPUNIT_ASSERT_EQUAL(targetPositionFetcher.getEnemyGoalPosition().front(),rightSide*(-1));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballInTheMiddle_goalieIsAtYBallPosition()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	BallMock ball;
	ball.setBallPosition(Point(0,0));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0,0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballOnTheSideFieldSideRight_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	BallMock ball;
	ball.setBallPosition(Point(0,0.5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.04,0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballOnTheSideFieldSideLeft_goaliePositionIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	BallMock ball;
	ball.setBallPosition(Point(0,0.5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.04,0.0001);
}

void TargetPositionFetcherTest::getPenaltyPositionKicker_ballAtCenter_robotIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	BallMock ball;
	ball.setBallPosition(Point(0,0));

	CPPUNIT_ASSERT_EQUAL(Pose(Point(-0.05,0),Angle()),targetPositionFetcher.getPenaltyPositionKicker(ball));
}
