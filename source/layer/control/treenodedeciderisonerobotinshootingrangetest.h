#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISONEROBOTINSHOOTINGRANGETEST_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISONEROBOTINSHOOTINGRANGETEST_H

#include "layer/control/treenodetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeDeciderIsOneRobotInShootingRangeTest :
		public TreeNodeTest
	{
		CPPUNIT_TEST_SUITE(TreeNodeDeciderIsOneRobotInShootingRangeTest);
		CPPUNIT_TEST(decide_robotIsInShootingRange_shoot);
		CPPUNIT_TEST(decide_robotIsNotInShootingRange_isRobotBehindBall);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual TreeNode* createTestNode();

	private:
		void decide_robotIsInShootingRange_shoot();
		void decide_robotIsNotInShootingRange_isRobotBehindBall();

	};
}
}
}

#endif


