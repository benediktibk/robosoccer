#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TARGETPOSITIONFETCHERTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TARGETPOSITIONFETCHERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <vector>
#include "common/geometry/pose.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class TargetPositionFetcherTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(TargetPositionFetcherTest);
		CPPUNIT_TEST(getEnemyGoalPosition_bothSides_middlePosotionIsCorrect);
		CPPUNIT_TEST(getOwnGoalPosition_ballInTheMiddle_goalieIsAtYBallPosition);
		CPPUNIT_TEST(getOwnGoalPosition_ballOnTheSideFieldSideRight_goaliePositionIsCorrect);
		CPPUNIT_TEST(getOwnGoalPosition_ballOnTheSideFieldSideLeft_goaliePositionIsCorrect);
		CPPUNIT_TEST(getPenaltyPositionKicker_ballAtCenter_robotIsCorrect);
		CPPUNIT_TEST(getPenaltyPositionKicker_ballNotAtCenter_distanceToBallIsBigEnough);
		CPPUNIT_TEST(getPenaltyPositionKicker_ballNotAtCenter_distanceToBallIsNotTooBig);
		CPPUNIT_TEST(getPenaltyPositionGoalie_ballOnTheSide_goaliePositionIsCorrect);
		CPPUNIT_TEST(getOwnGoalPosition_ballInOwnHalfAndDirectionNotOnGoal_goaliePositionIsCorrect);
		CPPUNIT_TEST(getOwnGoalPosition_ballNotInOwnHalf_goaliePositionIsCorrect);
		CPPUNIT_TEST(getOwnGoalPosition_ballInOwnHalfAndDirectionLikelyOnGoal_goaliePositionIsCorrect);
		CPPUNIT_TEST(getOwnGoalPosition_ballInOwnHalfAndDirectionLikelyNotOnGoal_goaliePositionIsCorrect);
		CPPUNIT_TEST(getPenaltyPositionUnusedOne_fieldSideRightOrLeft_robotIsOnRightSide);
		CPPUNIT_TEST(getPenaltyPositionUnusedTwo_fieldSideLeftOrRight_robotIsCorrect);
		CPPUNIT_TEST(getPenaltyPositionPrepareKicker_ball_positionInCorrectArea);
		CPPUNIT_TEST(getPenaltyPositionPrepareKicker_ball_angleIsCorrect);
		CPPUNIT_TEST(getPenaltyPositionGoalie_ballBehindGoalie_goaliePositionIsCorrect);
		CPPUNIT_TEST(getPenaltyPositionGoalie_ballNotMovingAtRightFieldSide_goaliePositionIsInUsefulRange);
		CPPUNIT_TEST(getPenaltyPositionGoalie_ballNotMovingAtLeftFieldSide_goaliePositionIsInUsefulRange);
		CPPUNIT_TEST(getPenaltyPositionGoalie_ballNotMovingAtRightFieldSideAtUpperSide_goaliePositionIsInUsefulRange);
		CPPUNIT_TEST(getPenaltyPositionGoalie_ballNotMovingAtRightFieldSideAtLowerSide_goaliePositionIsInUsefulRange);
		CPPUNIT_TEST(getPenaltyPositionGoalie_ballNotMovingAtLeftFieldSideAtUpperSide_goaliePositionIsInUsefulRange);
		CPPUNIT_TEST(getPenaltyPositionGoalie_ballNotMovingAtLeftFieldSideAtLowerSide_goaliePositionIsInUsefulRange);
		CPPUNIT_TEST(getPenaltyPositionGoalie_ballMovingRightAtLeftFieldSide_goaliePositionIsInUsefulRange);
		CPPUNIT_TEST(getPenaltyPositionGoalie_ballMovingLeftAtLeftFieldSide_goaliePositionIsInUsefulRange);
		CPPUNIT_TEST(getEnemyGoalPosition_fieldSideRight_positionAreLeft);
		CPPUNIT_TEST(getPointBehindBallInMovingDirection_ballAtZeroZeroMovingToDirectionZeroOne_zeroAndZeroPointTwo);
		CPPUNIT_TEST(getPointBehindBallInMovingDirection_ballAMinusTwoTwoMovingToDirectionMinusOneMinusOne_minusThreeAndOne);
		CPPUNIT_TEST(getPointBehindBallInMovingDirection_ballATwoMinusOneMovingToDirectionOneZero_threeAndMinusOne);
		CPPUNIT_TEST(getAlternativeRobotPositionsBehindBallAggressiveMode_fieldSideLeftAndBallOnFieldSideRight_positionBehindBall);
		CPPUNIT_TEST(getAlternativeRobotPositionsBehindBallAggressiveMode_fieldSideRighttAndBallOnFieldSideLeft_positionBehindBall);
		CPPUNIT_TEST(getAlternativeRobotPositionsBehindBallAggressiveMode_fieldSideLeftAndBallOnFieldSideRightAndNearTheSideBorder_positionOnMaxY);
		CPPUNIT_TEST(isGoodKickPosition_robotInGoodPosition_true);
		CPPUNIT_TEST(getAlternativeRobotPositionAtBallHeightAggressiveMode_noIntersectionPoint_atLeastSomePoints);
		CPPUNIT_TEST(getPositionToDriveOnBall_validBallPosition_fiveResults);
		CPPUNIT_TEST(getPositionToDriveOnBall_ballXAt1_threeXAre1);
		CPPUNIT_TEST(getPositionToDriveOnBall_ballYAt2_threeYAre2);
		CPPUNIT_TEST(getPositionToDriveOnBall_ballAt1And2_firstPositionIs1And2);
		CPPUNIT_TEST(isGoodKickPosition_robotInBadPositionDueToDistanceViolation_false);
		CPPUNIT_TEST(isGoodKickPosition_robotInBadPositionDueToAngleViolation_false);
		CPPUNIT_TEST(isGoodKickPosition_robotInGoodKickPosition_true);
		CPPUNIT_TEST(isGoodKickPosition_robotInGoodAnglePositionButBallInsideGoalZone_false);
		CPPUNIT_TEST(isGoodKickPosition_ballOnGoalBorderAndRobotBehind_true);
		CPPUNIT_TEST(isGoodKickPosition_ballOnGoalBorderInsideGoalZoneAndRobotBehind_false);
		CPPUNIT_TEST(getPositionsToGetOutOfGoalZone_fieldSideRight_positionsAreLeft);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getEnemyGoalPosition_bothSides_middlePosotionIsCorrect();
		void getOwnGoalPosition_ballInTheMiddle_goalieIsAtYBallPosition();
		void getOwnGoalPosition_ballOnTheSideFieldSideRight_goaliePositionIsCorrect();
		void getOwnGoalPosition_ballOnTheSideFieldSideLeft_goaliePositionIsCorrect();
		void getPenaltyPositionKicker_ballAtCenter_robotIsCorrect();
		void getPenaltyPositionKicker_ballNotAtCenter_distanceToBallIsBigEnough();
		void getPenaltyPositionKicker_ballNotAtCenter_distanceToBallIsNotTooBig();
		void getPenaltyPositionGoalie_ballOnTheSide_goaliePositionIsCorrect();
		void getOwnGoalPosition_ballInOwnHalfAndDirectionNotOnGoal_goaliePositionIsCorrect();
		void getOwnGoalPosition_ballNotInOwnHalf_goaliePositionIsCorrect();
		void getOwnGoalPosition_ballInOwnHalfAndDirectionLikelyOnGoal_goaliePositionIsCorrect();
		void getOwnGoalPosition_ballInOwnHalfAndDirectionLikelyNotOnGoal_goaliePositionIsCorrect();
		void getPenaltyPositionUnusedOne_fieldSideRightOrLeft_robotIsOnRightSide();
		void getPenaltyPositionUnusedTwo_fieldSideLeftOrRight_robotIsCorrect();
		void getPenaltyPositionPrepareKicker_ball_positionInCorrectArea();
		void getPenaltyPositionPrepareKicker_ball_angleIsCorrect();
		void getPenaltyPositionGoalie_ballBehindGoalie_goaliePositionIsCorrect();
		void getPenaltyPositionGoalie_ballNotMovingAtRightFieldSide_goaliePositionIsInUsefulRange();
		void getPenaltyPositionGoalie_ballNotMovingAtLeftFieldSide_goaliePositionIsInUsefulRange();
		void getPenaltyPositionGoalie_ballNotMovingAtRightFieldSideAtUpperSide_goaliePositionIsInUsefulRange();
		void getPenaltyPositionGoalie_ballNotMovingAtRightFieldSideAtLowerSide_goaliePositionIsInUsefulRange();
		void getPenaltyPositionGoalie_ballNotMovingAtLeftFieldSideAtUpperSide_goaliePositionIsInUsefulRange();
		void getPenaltyPositionGoalie_ballNotMovingAtLeftFieldSideAtLowerSide_goaliePositionIsInUsefulRange();
		void getPenaltyPositionGoalie_ballMovingRightAtLeftFieldSide_goaliePositionIsInUsefulRange();
		void getPenaltyPositionGoalie_ballMovingLeftAtLeftFieldSide_goaliePositionIsInUsefulRange();
		void getEnemyGoalPosition_fieldSideRight_positionAreLeft();
		void getPointBehindBallInMovingDirection_ballAtZeroZeroMovingToDirectionZeroOne_zeroAndZeroPointTwo();
		void getPointBehindBallInMovingDirection_ballAMinusTwoTwoMovingToDirectionMinusOneMinusOne_minusThreeAndOne();
		void getPointBehindBallInMovingDirection_ballATwoMinusOneMovingToDirectionOneZero_threeAndMinusOne();
		void getAlternativeRobotPositionsBehindBallAggressiveMode_fieldSideLeftAndBallOnFieldSideRight_positionBehindBall();
		void getAlternativeRobotPositionsBehindBallAggressiveMode_fieldSideRighttAndBallOnFieldSideLeft_positionBehindBall();
		void getAlternativeRobotPositionsBehindBallAggressiveMode_fieldSideLeftAndBallOnFieldSideRightAndNearTheSideBorder_positionOnMaxY();
		void isGoodKickPosition_robotInGoodPosition_true();
		void getAlternativeRobotPositionAtBallHeightAggressiveMode_noIntersectionPoint_atLeastSomePoints();
		void getPositionToDriveOnBall_validBallPosition_fiveResults();
		void getPositionToDriveOnBall_ballXAt1_threeXAre1();
		void getPositionToDriveOnBall_ballYAt2_threeYAre2();
		void getPositionToDriveOnBall_ballAt1And2_firstPositionIs1And2();
		void isGoodKickPosition_robotInBadPositionDueToDistanceViolation_false();
		void isGoodKickPosition_robotInBadPositionDueToAngleViolation_false();
		void isGoodKickPosition_robotInGoodKickPosition_true();
		void isGoodKickPosition_robotInGoodAnglePositionButBallInsideGoalZone_false();
		void isGoodKickPosition_ballOnGoalBorderAndRobotBehind_true();
		void isGoodKickPosition_ballOnGoalBorderInsideGoalZoneAndRobotBehind_false();
		void getPositionsToGetOutOfGoalZone_fieldSideRight_positionsAreLeft();

	private:
		void isInUsefulRange(Common::Geometry::Pose const &pose, double distanceToGoal, bool left);
		void isInUsefulRange(Common::Geometry::Point const &position, double distanceToGoal, bool left);
		void isInUsefulRange(std::vector<Common::Geometry::Pose> const &poses, double distanceToGoal, bool left);
	};
}
}
}

#endif
