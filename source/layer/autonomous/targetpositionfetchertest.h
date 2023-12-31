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
		CPPUNIT_TEST(getTargetForGoalkeeper_ballInTheMiddle_goalieIsAtYBallPosition);
		CPPUNIT_TEST(getTargetForGoalkeeper_ballOnTheSideFieldSideRight_goaliePositionIsCorrect);
		CPPUNIT_TEST(getTargetForGoalkeeper_ballOnTheSideFieldSideLeft_goaliePositionIsCorrect);
		CPPUNIT_TEST(getTargetForGoalkeeper_ballMovingTowardsTheGoalInAVerySharpAngle_positionIsAtEdgeOfGoal);
		CPPUNIT_TEST(getPenaltyPositionKicker_ballAtCenter_robotIsCorrect);
		CPPUNIT_TEST(getPenaltyPositionKicker_ballNotAtCenter_distanceToBallIsBigEnough);
		CPPUNIT_TEST(getPenaltyPositionKicker_ballNotAtCenter_distanceToBallIsNotTooBig);
		CPPUNIT_TEST(getPenaltyPositionGoalie_ballOnTheSide_goaliePositionIsCorrect);
		CPPUNIT_TEST(getTargetForGoalkeeper_ballInOwnHalfAndDirectionNotOnGoal_goaliePositionIsCorrect);
		CPPUNIT_TEST(getTargetForGoalkeeper_ballNotInOwnHalf_goaliePositionIsCorrect);
		CPPUNIT_TEST(getTargetForGoalkeeper_ballInOwnHalfAndDirectionLikelyOnGoal_goaliePositionIsCorrect);
		CPPUNIT_TEST(getTargetForGoalkeeper_ballInOwnHalfAndDirectionLikelyNotOnGoal_goaliePositionIsCorrect);
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
		CPPUNIT_TEST(getAlternativeRobotPositionsBehindBallAggressiveMode_fieldSideLeftAndBallOnFieldSideRight_positionBehindBall);
		CPPUNIT_TEST(getAlternativeRobotPositionsBehindBallAggressiveMode_fieldSideRighttAndBallOnFieldSideLeft_positionBehindBall);
		CPPUNIT_TEST(getAlternativeRobotPositionsBehindBallAggressiveMode_fieldSideLeftAndBallOnFieldSideRightAndNearTheSideBorder_positionOnMaxY);
		CPPUNIT_TEST(isGoodKickPosition_robotInGoodPosition_true);
		CPPUNIT_TEST(getAlternativeRobotPositionBehindBallAggressiveMode_fieldSideLeftAndBallNearToGoal_positionInUsefulArea);
		CPPUNIT_TEST(getPositionToDriveOnBall_validBallPosition_atLeastTenResults);
		CPPUNIT_TEST(getPositionToDriveOnBall_ballXAt1_atLeastThreeXAre1);
		CPPUNIT_TEST(getPositionToDriveOnBall_ballYAt2_atLeastThreeYAre2);
		CPPUNIT_TEST(getPositionToDriveOnBall_ballAt1And2_firstPositionIs1And2);
		CPPUNIT_TEST(isGoodKickPosition_robotInBadPositionDueToDistanceViolation_false);
		CPPUNIT_TEST(isGoodKickPosition_robotInBadPositionDueToAngleViolation_false);
		CPPUNIT_TEST(isGoodKickPosition_robotInGoodKickPosition_true);
		CPPUNIT_TEST(isGoodKickPosition_robotInGoodAnglePositionButBallInsideGoalZone_false);
		CPPUNIT_TEST(isGoodKickPosition_ballOnGoalBorderAndRobotBehind_true);
		CPPUNIT_TEST(isGoodKickPosition_ballOnGoalBorderInsideGoalZoneAndRobotBehind_false);
		CPPUNIT_TEST(getPositionsToGetOutOfGoalZone_fieldSideRight_positionsAreLeft);
		CPPUNIT_TEST(getTargetsBehindBallAlternativeRobot_ballAtCenter_positionsBetweenGoalAndBall);
		CPPUNIT_TEST(isGoodKickPosition_nearOwnBorderRightFromGoalAndLeftFromBall_true);
		CPPUNIT_TEST(isGoodKickPosition_nearOwnBorderRightFromGoalAndRightFromBall_false);
		CPPUNIT_TEST(isGoodKickPosition_nearOwnBorderLeftFromGoalAndLeftFromBall_false);
		CPPUNIT_TEST(isGoodKickPosition_nearOwnBorderLeftFromGoalAndRightFromBall_true);
		CPPUNIT_TEST(isGoodKickPosition_nearEnemyBorderRightFromGoalAndLeftFromBall_false);
		CPPUNIT_TEST(isGoodKickPosition_nearEnemyBorderLeftFromGoalAndLeftFromBall_false);
		CPPUNIT_TEST(isGoodKickPosition_nearOwnBorderLeftFromGoalButRobotBehindBall_true);
		CPPUNIT_TEST(isGoodKickPosition_nearOwnBorderRightFromGoalButRobotBehindBall_true);
		CPPUNIT_TEST(isGoodKickPosition_nearOwnBorderRightFromGoalAndInfrontOfGoalZoneAndRobotAimsToOwnGoal_false);
		CPPUNIT_TEST(isGoodKickPosition_nearOwnBorderRightFromGoalAndInfrontOfGoalZoneAndRobotAimsNotToOwnGoal_true);
		CPPUNIT_TEST(getPenaltyPositionPrepareGoalie_true_correctStartPosition);
		CPPUNIT_TEST(isPointBehindBallWithAngle_quarterRotationAndLeftSideAndPointIsDirectlyBehindBall_true);
		CPPUNIT_TEST(isPointBehindBallWithAngle_halfRotationAndRightSideAndPointIsDirectlyOppositeToBall_false);
		CPPUNIT_TEST(isPointBehindBallWithAngle_halfRotationAndRightSideAndPointIsNextToBall_true);
		CPPUNIT_TEST(isPointBehindBall_rightSideAndPointIsNextToBall_false);
		CPPUNIT_TEST(isPointBehindBall_leftSideAndPointBehindBall_true);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getEnemyGoalPosition_bothSides_middlePosotionIsCorrect();
		void getTargetForGoalkeeper_ballInTheMiddle_goalieIsAtYBallPosition();
		void getTargetForGoalkeeper_ballOnTheSideFieldSideRight_goaliePositionIsCorrect();
		void getTargetForGoalkeeper_ballOnTheSideFieldSideLeft_goaliePositionIsCorrect();
		void getTargetForGoalkeeper_ballMovingTowardsTheGoalInAVerySharpAngle_positionIsAtEdgeOfGoal();
		void getPenaltyPositionKicker_ballAtCenter_robotIsCorrect();
		void getPenaltyPositionKicker_ballNotAtCenter_distanceToBallIsBigEnough();
		void getPenaltyPositionKicker_ballNotAtCenter_distanceToBallIsNotTooBig();
		void getPenaltyPositionGoalie_ballOnTheSide_goaliePositionIsCorrect();
		void getTargetForGoalkeeper_ballInOwnHalfAndDirectionNotOnGoal_goaliePositionIsCorrect();
		void getTargetForGoalkeeper_ballNotInOwnHalf_goaliePositionIsCorrect();
		void getTargetForGoalkeeper_ballInOwnHalfAndDirectionLikelyOnGoal_goaliePositionIsCorrect();
		void getTargetForGoalkeeper_ballInOwnHalfAndDirectionLikelyNotOnGoal_goaliePositionIsCorrect();
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
		void getAlternativeRobotPositionsBehindBallAggressiveMode_fieldSideLeftAndBallOnFieldSideRight_positionBehindBall();
		void getAlternativeRobotPositionsBehindBallAggressiveMode_fieldSideRighttAndBallOnFieldSideLeft_positionBehindBall();
		void getAlternativeRobotPositionsBehindBallAggressiveMode_fieldSideLeftAndBallOnFieldSideRightAndNearTheSideBorder_positionOnMaxY();
		void isGoodKickPosition_robotInGoodPosition_true();
		void getAlternativeRobotPositionBehindBallAggressiveMode_fieldSideLeftAndBallNearToGoal_positionInUsefulArea();
		void getPositionToDriveOnBall_validBallPosition_atLeastTenResults();
		void getPositionToDriveOnBall_ballXAt1_atLeastThreeXAre1();
		void getPositionToDriveOnBall_ballYAt2_atLeastThreeYAre2();
		void getPositionToDriveOnBall_ballAt1And2_firstPositionIs1And2();
		void isGoodKickPosition_robotInBadPositionDueToDistanceViolation_false();
		void isGoodKickPosition_robotInBadPositionDueToAngleViolation_false();
		void isGoodKickPosition_robotInGoodKickPosition_true();
		void isGoodKickPosition_robotInGoodAnglePositionButBallInsideGoalZone_false();
		void isGoodKickPosition_ballOnGoalBorderAndRobotBehind_true();
		void isGoodKickPosition_ballOnGoalBorderInsideGoalZoneAndRobotBehind_false();
		void getPositionsToGetOutOfGoalZone_fieldSideRight_positionsAreLeft();
		void getTargetsBehindBallAlternativeRobot_ballAtCenter_positionsBetweenGoalAndBall();
		void isGoodKickPosition_nearOwnBorderRightFromGoalAndLeftFromBall_true();
		void isGoodKickPosition_nearOwnBorderRightFromGoalAndRightFromBall_false();
		void isGoodKickPosition_nearOwnBorderLeftFromGoalAndLeftFromBall_false();
		void isGoodKickPosition_nearOwnBorderLeftFromGoalAndRightFromBall_true();
		void isGoodKickPosition_nearEnemyBorderRightFromGoalAndLeftFromBall_false();
		void isGoodKickPosition_nearEnemyBorderLeftFromGoalAndLeftFromBall_false();
		void isGoodKickPosition_nearOwnBorderLeftFromGoalButRobotBehindBall_true();
		void isGoodKickPosition_nearOwnBorderRightFromGoalButRobotBehindBall_true();
		void isGoodKickPosition_nearOwnBorderRightFromGoalAndInfrontOfGoalZoneAndRobotAimsToOwnGoal_false();
		void isGoodKickPosition_nearOwnBorderRightFromGoalAndInfrontOfGoalZoneAndRobotAimsNotToOwnGoal_true();
		void getPenaltyPositionPrepareGoalie_true_correctStartPosition();
		void isPointBehindBallWithAngle_quarterRotationAndLeftSideAndPointIsDirectlyBehindBall_true();
		void isPointBehindBallWithAngle_halfRotationAndRightSideAndPointIsDirectlyOppositeToBall_false();
		void isPointBehindBallWithAngle_halfRotationAndRightSideAndPointIsNextToBall_true();
		void isPointBehindBall_rightSideAndPointIsNextToBall_false();
		void isPointBehindBall_leftSideAndPointBehindBall_true();

	private:
		void isInUsefulRange(Common::Geometry::Pose const &pose, double distanceToGoal, bool left);
		void isInUsefulRange(Common::Geometry::Point const &position, double distanceToGoal, bool left);
		void isInUsefulRange(std::vector<Common::Geometry::Pose> const &poses, double distanceToGoal, bool left);

		void isInUsefulArea(Common::Geometry::Point const &position, double maxX, double maxY);
	};
}
}
}

#endif
