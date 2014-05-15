#include "layer/autonomous/targetpositionfetchertest.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/abstraction/fieldside.h"
#include "layer/autonomous/intelligentballmock.h"
#include "common/geometry/pose.h"
#include "common/geometry/compare.h"
#include "common/geometry/rectangle.h"
#include "common/other/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Abstraction;
using namespace std;

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

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0,targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballOnTheSideFieldSideRight_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	IntelligentBallMock ball;
	ball.setPosition(Point(0,0.5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.04,targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballOnTheSideFieldSideLeft_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	IntelligentBallMock ball;
	ball.setPosition(Point(0,0.5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.04,targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getPenaltyPositionKicker_ballAtCenter_robotIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(0,0));

	CPPUNIT_ASSERT_EQUAL(Pose(Point(0.08, 0),Angle::getHalfRotation()), targetPositionFetcher.getPenaltyPositionKicker(ball));
}

void TargetPositionFetcherTest::getPenaltyPositionKicker_ballNotAtCenter_distanceToBallIsBigEnough()
{
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	Point ballPosition(0.5, -0.2);
	ball.setPosition(ballPosition);

	Pose targetPose = targetPositionFetcher.getPenaltyPositionKicker(ball);

	Point const &targetPosition = targetPose.getPosition();
	double distanceToBall = targetPosition.distanceTo(ballPosition);
	double radiusRobot = 0.05;
	double radiusBall = 0.025;
	CPPUNIT_ASSERT(distanceToBall >= radiusRobot + radiusBall);
}

void TargetPositionFetcherTest::getPenaltyPositionKicker_ballNotAtCenter_distanceToBallIsNotTooBig()
{
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	Point ballPosition(0.5, -0.2);
	ball.setPosition(ballPosition);

	Pose targetPose = targetPositionFetcher.getPenaltyPositionKicker(ball);

	Point const &targetPosition = targetPose.getPosition();
	double distanceToBall = targetPosition.distanceTo(ballPosition);
	double radiusRobot = 0.05;
	double radiusBall = 0.025;
	CPPUNIT_ASSERT(distanceToBall <= radiusRobot + radiusBall + 0.05);
}

void TargetPositionFetcherTest::getPenaltyPositionGoalie_ballOnTheSide_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(0,0.5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.25/3,targetPositionFetcher.getPenaltyPositionGoalie(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getPenaltyPositionGoalie(ball).getOrientation()));
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

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.06,targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
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

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.03,targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
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

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1,targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
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

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0,targetPositionFetcher.getOwnGoalPosition(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getOwnGoalPosition(ball).getOrientation()));
}

void TargetPositionFetcherTest::getPenaltyPositionUnusedOne_fieldSideRightOrLeft_robotIsOnRightSide()
{
	TargetPositionFetcher targetPositionFetcher;

	targetPositionFetcher.setFieldSide(FieldSideRight);
	CPPUNIT_ASSERT(targetPositionFetcher.getPenaltyPositionsUnusedPlayerOne().front().getPosition().getX() > 0);

	targetPositionFetcher.setFieldSide(FieldSideLeft);
	CPPUNIT_ASSERT(targetPositionFetcher.getPenaltyPositionsUnusedPlayerOne().front().getPosition().getX() > 0);
}

void TargetPositionFetcherTest::getPenaltyPositionUnusedTwo_fieldSideLeftOrRight_robotIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;

	targetPositionFetcher.setFieldSide(FieldSideLeft);
	CPPUNIT_ASSERT(targetPositionFetcher.getPenaltyPositionsUnusedPlayerTwo().front().getPosition().getX() > 0);

	targetPositionFetcher.setFieldSide(FieldSideRight);
	CPPUNIT_ASSERT(targetPositionFetcher.getPenaltyPositionsUnusedPlayerTwo().front().getPosition().getX() > 0);
}

void TargetPositionFetcherTest::getPenaltyPositionPrepareKicker_ball_positionInCorrectArea()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);

	Rectangle targetArea(Point(-0.3, -0.3), Point(0.3, 0.3));

	CPPUNIT_ASSERT(targetArea.isInside(targetPositionFetcher.getPenaltyPositionPrepareKicker().getPosition(), Common::Other::Compare(0.1)));
}

void TargetPositionFetcherTest::getPenaltyPositionPrepareKicker_ball_angleIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);

	Compare compare(0.1);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(), targetPositionFetcher.getPenaltyPositionPrepareKicker().getOrientation()));
}

void TargetPositionFetcherTest::getPenaltyPositionGoalie_ballBehindGoalie_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(-1.45,0.5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2,targetPositionFetcher.getPenaltyPositionGoalie(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getPenaltyPositionGoalie(ball).getOrientation()));
}

void TargetPositionFetcherTest::getPenaltyPositionGoalie_ballNotMovingAtRightFieldSide_goaliePositionIsInUsefulRange()
{
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(0.5, 0));
	ball.setIsMoving(false);
	ball.setCurrentFieldSide(FieldSideRight);

	Point target = targetPositionFetcher.getPenaltyPositionGoalie(ball);

	isInUsefulRange(target, 0.2, true);
}

void TargetPositionFetcherTest::getPenaltyPositionGoalie_ballNotMovingAtLeftFieldSide_goaliePositionIsInUsefulRange()
{
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(-0.5, 0));
	ball.setIsMoving(false);
	ball.setCurrentFieldSide(FieldSideLeft);

	Point target = targetPositionFetcher.getPenaltyPositionGoalie(ball);

	isInUsefulRange(target, 0.2, true);
}

void TargetPositionFetcherTest::getPenaltyPositionGoalie_ballNotMovingAtRightFieldSideAtUpperSide_goaliePositionIsInUsefulRange()
{
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(0.5, 0.5));
	ball.setIsMoving(false);
	ball.setCurrentFieldSide(FieldSideRight);

	Point target = targetPositionFetcher.getPenaltyPositionGoalie(ball);

	isInUsefulRange(target, 0.2, true);
}

void TargetPositionFetcherTest::getPenaltyPositionGoalie_ballNotMovingAtRightFieldSideAtLowerSide_goaliePositionIsInUsefulRange()
{
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(0.5, -0.5));
	ball.setIsMoving(false);
	ball.setCurrentFieldSide(FieldSideRight);

	Point target = targetPositionFetcher.getPenaltyPositionGoalie(ball);

	isInUsefulRange(target, 0.2, true);
}

void TargetPositionFetcherTest::getPenaltyPositionGoalie_ballNotMovingAtLeftFieldSideAtUpperSide_goaliePositionIsInUsefulRange()
{
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(-0.5, 0.5));
	ball.setIsMoving(false);
	ball.setCurrentFieldSide(FieldSideLeft);

	Point target = targetPositionFetcher.getPenaltyPositionGoalie(ball);

	isInUsefulRange(target, 0.2, true);
}

void TargetPositionFetcherTest::getPenaltyPositionGoalie_ballNotMovingAtLeftFieldSideAtLowerSide_goaliePositionIsInUsefulRange()
{
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(-0.5, -0.5));
	ball.setIsMoving(false);
	ball.setCurrentFieldSide(FieldSideLeft);

	Point target = targetPositionFetcher.getPenaltyPositionGoalie(ball);

	isInUsefulRange(target, 0.2, true);
}

void TargetPositionFetcherTest::getPenaltyPositionGoalie_ballMovingRightAtLeftFieldSide_goaliePositionIsInUsefulRange()
{

	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(-0.5, 0));
	ball.setIsMoving(true);
	ball.setCurrentFieldSide(FieldSideLeft);
	ball.setMovingDirection(FieldSideRight);

	Point target = targetPositionFetcher.getPenaltyPositionGoalie(ball);

	isInUsefulRange(target, 0.2, true);
}

void TargetPositionFetcherTest::getPenaltyPositionGoalie_ballMovingLeftAtLeftFieldSide_goaliePositionIsInUsefulRange()
{
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(-0.5, 0));
	ball.setIsMoving(true);
	ball.setCurrentFieldSide(FieldSideLeft);
	ball.setMovingDirection(FieldSideLeft);

	Point target = targetPositionFetcher.getPenaltyPositionGoalie(ball);

	isInUsefulRange(target, 0.2, true);
}

void TargetPositionFetcherTest::getEnemyGoalPosition_fieldSideRight_positionAreLeft()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);

	for(unsigned int i = 0; i<targetPositionFetcher.getEnemyGoalPosition().size(); i++)
		CPPUNIT_ASSERT(targetPositionFetcher.getEnemyGoalPosition()[i].getX() < 0);
}

void TargetPositionFetcherTest::isInUsefulRange(const Pose &pose, double distanceToGoal, bool left)
{
	Point const &position = pose.getPosition();
	Angle const &orientation = pose.getOrientation();

	Compare compare(0.00001);
	isInUsefulRange(position, distanceToGoal, left);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(orientation, Angle::getQuarterRotation()) || compare.isFuzzyEqual(orientation, Angle::getQuarterRotation()*(-1)));
}

void TargetPositionFetcherTest::isInUsefulRange(const Point &position, double distanceToGoal, bool left)
{
	if (left)
		CPPUNIT_ASSERT(position.getX() < 0);
	else
		CPPUNIT_ASSERT(position.getX() > 0);

	double xModified = position.getX() * (left ? -1 : 1);
	double realDistanceToGoal = 1.45 - xModified;
	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(realDistanceToGoal, distanceToGoal));
	CPPUNIT_ASSERT(position.getY() < 0.36);
	CPPUNIT_ASSERT(position.getY() > -0.36);
}

void TargetPositionFetcherTest::isInUsefulRange(const vector<Pose> &poses, double distanceToGoal, bool left)
{
	for (vector<Pose>::const_iterator i = poses.begin(); i != poses.end(); ++i)
		isInUsefulRange(*i, distanceToGoal, left);
}
