#include "layer/autonomous/targetpositionfetchertest.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "common/geometry/pose.h"
#include "layer/abstraction/fieldside.h"
#include "layer/autonomous/intelligentballmock.h"
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
	IntelligentBallMock ball;
	ball.setPosition(Point(0,0));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0,0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballOnTheSideFieldSideRight_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	IntelligentBallMock ball;
	ball.setPosition(Point(0,0.5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.04,0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballOnTheSideFieldSideLeft_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	IntelligentBallMock ball;
	ball.setPosition(Point(0,0.5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.04,0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getPenaltyPositionKicker_ballAtCenter_robotIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	IntelligentBallMock ball;
	ball.setPosition(Point(0,0));

	CPPUNIT_ASSERT_EQUAL(Pose(Point(-0.05,0),Angle()),targetPositionFetcher.getPenaltyPositionKicker(ball));
}

void TargetPositionFetcherTest::getPenaltyPositionGoalie_ballOnTheSideFieldSideRight_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	IntelligentBallMock ball;
	ball.setPosition(Point(0,0.5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getPenaltyPositionGoalie(ball).getPosition().getY(),0.25/3,0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballInOwnHalfAndDirectionNotOnGoal_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	IntelligentBallMock ball;
	ball.setPosition(Point(0.5,0.5));
	ball.setIsMoving(true);
	ball.setMovingDirection(FieldSideLeft);
	ball.setCurrentFieldSide(FieldSideRight);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.06,0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballNotInOwnHalf_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	IntelligentBallMock ball;
	ball.setPosition(Point(-0.5,0.5));
	ball.setIsMoving(true);
	ball.setMovingDirection(FieldSideRight);
	ball.setCurrentFieldSide(FieldSideLeft);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.03,0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballInOwnHalfAndDirectionLikelyOnGoal_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	IntelligentBallMock ball;
	ball.setPosition(Point(0.38,0));
	ball.setIsMoving(true);
	ball.setMovingDirection(FieldSideRight);
	ball.setCurrentFieldSide(FieldSideRight);
	ball.setRotation(Angle(0.1));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.1,0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballInOwnHalfAndDirectionLikelyNotOnGoal_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	IntelligentBallMock ball;
	ball.setPosition(Point(0.5,0));
	ball.setIsMoving(true);
	ball.setMovingDirection(FieldSideRight);
	ball.setCurrentFieldSide(FieldSideRight);
	ball.setRotation(Angle::getEighthRotation());

	CPPUNIT_ASSERT_DOUBLES_EQUAL(targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0,0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getPenaltyPositionUnusedOne_fieldSideRight_robotIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);

	CPPUNIT_ASSERT(targetPositionFetcher.getPenaltyPositionUnusedPlayerOne().getPosition().getX() < 0);
}

void TargetPositionFetcherTest::getPenaltyPositionUnusedTwo_fieldSideLeft_robotIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);

	CPPUNIT_ASSERT(targetPositionFetcher.getPenaltyPositionUnusedPlayerOne().getPosition().getX() > 0);
}
