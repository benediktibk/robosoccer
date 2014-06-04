#include "layer/autonomous/targetpositionfetchertest.h"
#include "layer/autonomous/targetpositionfetcher.h"
#include "layer/abstraction/fieldside.h"
#include "layer/autonomous/intelligentballmock.h"
#include "common/geometry/pose.h"
#include "common/geometry/compare.h"
#include "common/geometry/rectangle.h"
#include "common/other/compare.h"
#include <math.h>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common;
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

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0,targetPositionFetcher.getTargetForGoalkeeper(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getTargetForGoalkeeper(ball).getOrientation()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballOnTheSideFieldSideRight_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	IntelligentBallMock ball;
	ball.setPosition(Point(0,0.5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.04,targetPositionFetcher.getTargetForGoalkeeper(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getTargetForGoalkeeper(ball).getOrientation()));
}

void TargetPositionFetcherTest::getOwnGoalPosition_ballOnTheSideFieldSideLeft_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	IntelligentBallMock ball;
	ball.setPosition(Point(0,0.5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.04,targetPositionFetcher.getTargetForGoalkeeper(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getTargetForGoalkeeper(ball).getOrientation()));
}

void TargetPositionFetcherTest::getPenaltyPositionKicker_ballAtCenter_robotIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(0,0));

	CPPUNIT_ASSERT_EQUAL(Pose(Point(0.11, 0),Angle::getHalfRotation()), targetPositionFetcher.getPenaltyPositionKicker(ball));
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

	Pose target = targetPositionFetcher.getPenaltyPositionGoalie(ball);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.25/3, target.getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), target.getOrientation()));
	isInUsefulRange(target, 0.2, true);
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

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.06,targetPositionFetcher.getTargetForGoalkeeper(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getTargetForGoalkeeper(ball).getOrientation()));
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

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.03,targetPositionFetcher.getTargetForGoalkeeper(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getTargetForGoalkeeper(ball).getOrientation()));
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

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1,targetPositionFetcher.getTargetForGoalkeeper(ball).getPosition().getY(),0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getTargetForGoalkeeper(ball).getOrientation()));
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

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0,targetPositionFetcher.getTargetForGoalkeeper(ball).getPosition().getY(),0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(),targetPositionFetcher.getTargetForGoalkeeper(ball).getOrientation()));
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

	Pose target = targetPositionFetcher.getPenaltyPositionPrepareKicker();

	CPPUNIT_ASSERT(targetArea.isInside(target.getPosition(), Common::Other::Compare(0.1)));
}

void TargetPositionFetcherTest::getPenaltyPositionPrepareKicker_ball_angleIsCorrect()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	Compare compare(0.1);

	Pose target = targetPositionFetcher.getPenaltyPositionPrepareKicker();

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(), target.getOrientation()));
}

void TargetPositionFetcherTest::getPenaltyPositionGoalie_ballBehindGoalie_goaliePositionIsCorrect()
{
	Compare compare(0.001);
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(-1.45,0.5));

	Pose target = targetPositionFetcher.getPenaltyPositionGoalie(ball);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), target.getOrientation()));
	isInUsefulRange(target, 0.2, true);
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

void TargetPositionFetcherTest::getPointBehindBallInMovingDirection_ballAtZeroZeroMovingToDirectionZeroOne_zeroAndZeroPointTwo()
{
	Compare compare(0.00001);
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(0, 0));
	Angle ballRotation(Point(0,0),Point(0,1));
	ball.setRotation(ballRotation);
	ball.setIsMoving(true);

	Point shouldBe = targetPositionFetcher.getPointBehindBallInMovingDirection(ball, 0.2);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(shouldBe,Point(0,0.2)));
}

void TargetPositionFetcherTest::getPointBehindBallInMovingDirection_ballAMinusTwoTwoMovingToDirectionMinusOneMinusOne_minusThreeAndOne()
{
	Compare compare(0.00001);
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(-2, 2));
	Angle ballRotation(Point(0,0),Point(-1,-1));
	ball.setRotation(ballRotation);
	ball.setIsMoving(true);

	Point shouldBe = targetPositionFetcher.getPointBehindBallInMovingDirection(ball, sqrt(2.0));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(shouldBe,Point(-3,1)));
}

void TargetPositionFetcherTest::getPointBehindBallInMovingDirection_ballATwoMinusOneMovingToDirectionOneZero_threeAndMinusOne()
{
	Compare compare(0.00001);
	TargetPositionFetcher targetPositionFetcher;
	IntelligentBallMock ball;
	ball.setPosition(Point(2, -1));
	Angle ballRotation(Point(0,0),Point(1,0));
	ball.setRotation(ballRotation);
	ball.setIsMoving(true);

	Point shouldBe = targetPositionFetcher.getPointBehindBallInMovingDirection(ball, 1);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(shouldBe,Point(3,-1)));
}

void TargetPositionFetcherTest::getAlternativeRobotPositionAtBallHeightAggressiveMode_RobotAtZeroZeroBallAtPointFiveZero_ballposition()
{
	Compare compare(0.00001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	IntelligentBallMock ball;
	ball.setPosition(Point(0.5, 0));

	vector<Pose> shouldBe = targetPositionFetcher.getAlternativeRobotPositionAtBallHeightAggressiveMode(ball, Point(0,0));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(shouldBe.front().getPosition(), Point(0.5, 0)));
}

void TargetPositionFetcherTest::getAlternativeRobotPositionAtBallHeightAggressiveMode_RobotAtZeroZeroBallAtMinusPointFiveZero_ballposition()
{
	Compare compare(0.00001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	IntelligentBallMock ball;
	ball.setPosition(Point(-0.5, 0));

	vector<Pose> shouldBe = targetPositionFetcher.getAlternativeRobotPositionAtBallHeightAggressiveMode(ball, Point(0,0));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(shouldBe.front().getPosition(), Point(-0.5, 0)));
}


void TargetPositionFetcherTest::getAlternativeRobotPositionAtBallHeightAggressiveMode_RobotAtZeroZeroBallAtMinusPointFiveZero_ballpositionPlusZeroPointTwo()
{
	Compare compare(0.00001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	IntelligentBallMock ball;
	ball.setPosition(Point(-0.5, 0));

	vector<Pose> shouldBe = targetPositionFetcher.getAlternativeRobotPositionAtBallHeightAggressiveMode(ball, Point(0,0));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(shouldBe.at(1).getPosition(), Point(-0.5, 0.2)));
}

void TargetPositionFetcherTest::getAlternativeRobotPositionAtBallHeightAggressiveMode_RobotAtZeroZeroBallAtMinusPointFiveZero_ballpositionMinusZeroPointFour()
{
	Compare compare(0.00001);
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideRight);
	IntelligentBallMock ball;
	ball.setPosition(Point(-0.5, 0));

	vector<Pose> shouldBe = targetPositionFetcher.getAlternativeRobotPositionAtBallHeightAggressiveMode(ball, Point(0,0));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(shouldBe.at(4).getPosition(), Point(-0.5, -0.4)));
}

void TargetPositionFetcherTest::getAlternativeRobotPositionAtBallHeightAggressiveMode_noIntersectionPoint_atLeastSomePoints()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	IntelligentBallMock ball;
	ball.setPosition(Point(2, 0));
	Point robotPosition = targetPositionFetcher.getEnemyGoalPosition().front();

	vector<Pose> results = targetPositionFetcher.getAlternativeRobotPositionAtBallHeightAggressiveMode(ball, robotPosition);

	CPPUNIT_ASSERT(!results.empty());
}

void TargetPositionFetcherTest::getPositionToDriveOnBall_validBallPosition_fiveResults()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	IntelligentBallMock ball;
	ball.setPosition(Point(1, 2));

	vector<Pose> results = targetPositionFetcher.getPositionToDriveOnBall(ball);

	CPPUNIT_ASSERT_EQUAL((size_t)5, results.size());
}

void TargetPositionFetcherTest::getPositionToDriveOnBall_ballXAt1_threeXAre1()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	IntelligentBallMock ball;
	ball.setPosition(Point(1, 2));

	vector<Pose> results = targetPositionFetcher.getPositionToDriveOnBall(ball);

	unsigned int count = 0;
	Other::Compare compare(0.0001);
	for (vector<Pose>::const_iterator i = results.begin(); i != results.end(); ++i)
	{
		Pose const &pose = *i;
		Point const &position = pose.getPosition();
		if (compare.isFuzzyEqual(1, position.getX()))
			++count;
	}
	CPPUNIT_ASSERT_EQUAL((unsigned int)3, count);
}

void TargetPositionFetcherTest::getPositionToDriveOnBall_ballYAt2_threeYAre2()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	IntelligentBallMock ball;
	ball.setPosition(Point(1, 2));

	vector<Pose> results = targetPositionFetcher.getPositionToDriveOnBall(ball);

	unsigned int count = 0;
	Other::Compare compare(0.0001);
	for (vector<Pose>::const_iterator i = results.begin(); i != results.end(); ++i)
	{
		Pose const &pose = *i;
		Point const &position = pose.getPosition();
		if (compare.isFuzzyEqual(2, position.getY()))
			++count;
	}
	CPPUNIT_ASSERT_EQUAL((unsigned int)3, count);
}

void TargetPositionFetcherTest::getPositionToDriveOnBall_ballAt1And2_firstPositionIs1And2()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	IntelligentBallMock ball;
	ball.setPosition(Point(1, 2));

	vector<Pose> results = targetPositionFetcher.getPositionToDriveOnBall(ball);

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1, 2), results.front()));
}

void TargetPositionFetcherTest::isGoodKickPosition_robotInGoodPosition_true()
{
	TargetPositionFetcher targetPositionFetcher;
	targetPositionFetcher.setFieldSide(FieldSideLeft);
	IntelligentBallMock ball;
	ball.setPosition(Point(0.5,0.0));
	Point robotPosition(0.0,0.0);
	Angle spanAngle(M_PI*1/6);
	bool isGoodKickPosition = targetPositionFetcher.isGoodKickPosition(ball,robotPosition,spanAngle);
	CPPUNIT_ASSERT(isGoodKickPosition);
}
