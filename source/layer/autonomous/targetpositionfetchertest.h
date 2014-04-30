#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_TARGETPOSITIONFETCHERTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_TARGETPOSITIONFETCHERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

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
		CPPUNIT_TEST(getPenaltyPositionGoalie_ballOnTheSideFieldSideRight_goaliePositionIsCorrect);
		CPPUNIT_TEST(getOwnGoalPosition_ballInOwnHalfAndDirectionNotOnGoal_goaliePositionIsCorrect);
		CPPUNIT_TEST(getOwnGoalPosition_ballNotInOwnHalf_goaliePositionIsCorrect);
		CPPUNIT_TEST(getOwnGoalPosition_ballInOwnHalfAndDirectionLikelyOnGoal_goaliePositionIsCorrect);
		CPPUNIT_TEST(getOwnGoalPosition_ballInOwnHalfAndDirectionLikelyNotOnGoal_goaliePositionIsCorrect);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getEnemyGoalPosition_bothSides_middlePosotionIsCorrect();
		void getOwnGoalPosition_ballInTheMiddle_goalieIsAtYBallPosition();
		void getOwnGoalPosition_ballOnTheSideFieldSideRight_goaliePositionIsCorrect();
		void getOwnGoalPosition_ballOnTheSideFieldSideLeft_goaliePositionIsCorrect();
		void getPenaltyPositionKicker_ballAtCenter_robotIsCorrect();
		void getPenaltyPositionGoalie_ballOnTheSideFieldSideRight_goaliePositionIsCorrect();
		void getOwnGoalPosition_ballInOwnHalfAndDirectionNotOnGoal_goaliePositionIsCorrect();
		void getOwnGoalPosition_ballNotInOwnHalf_goaliePositionIsCorrect();
		void getOwnGoalPosition_ballInOwnHalfAndDirectionLikelyOnGoal_goaliePositionIsCorrect();
		void getOwnGoalPosition_ballInOwnHalfAndDirectionLikelyNotOnGoal_goaliePositionIsCorrect();
	};
}
}
}

#endif


