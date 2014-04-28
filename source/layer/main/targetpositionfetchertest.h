#ifndef ROBOSOCCER_LAYER_MAIN_TARGETPOSITIONFETCHERTEST_H
#define ROBOSOCCER_LAYER_MAIN_TARGETPOSITIONFETCHERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Layer
{
namespace Main
{
class TargetPositionFetcherTest :
		public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TargetPositionFetcherTest);
	CPPUNIT_TEST(getEnemyGoalPosition_bothSides_middlePosotionIsCorrect);
	CPPUNIT_TEST(getOwnGoalPosition_ballInTheMiddle_goalieIsAtYBallPosition);
	CPPUNIT_TEST(getOwnGoalPosition_ballOnTheSide_goalieIsAtGoalCornerPosition);
	CPPUNIT_TEST(getPenaltyPositionKicker_ballAtCenter_robotIsCorrect);
	CPPUNIT_TEST_SUITE_END();

private:
	void getEnemyGoalPosition_bothSides_middlePosotionIsCorrect();
	void getOwnGoalPosition_ballInTheMiddle_goalieIsAtYBallPosition();
	void getOwnGoalPosition_ballOnTheSide_goalieIsAtGoalCornerPosition();
	void getPenaltyPositionKicker_ballAtCenter_robotIsCorrect();

};
}
}
}

#endif


