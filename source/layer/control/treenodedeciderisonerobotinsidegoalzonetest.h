#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISONEROBOTINSIDEGOALZONETEST_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISONEROBOTINSIDEGOALZONETEST_H

#include "layer/control/treenodetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeDeciderIsOneRobotInsideGoalZoneTest :
		public TreeNodeTest
	{
		CPPUNIT_TEST_SUITE(TreeNodeDeciderIsOneRobotInsideGoalZoneTest);
		CPPUNIT_TEST(decide_robotsAreInValidPosition_isInShootingRange);
		CPPUNIT_TEST(decide_oneRobotInEnemyGoalZoneAndFieldSideLeft_leaveGoalZone);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual TreeNode* createTestNode();

	private:
		void decide_robotsAreInValidPosition_isInShootingRange();
		void decide_oneRobotInEnemyGoalZoneAndFieldSideLeft_leaveGoalZone();

	};
}
}
}

#endif


