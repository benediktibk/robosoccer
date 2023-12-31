#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODERESULTFOLLOWBALLTEST_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODERESULTFOLLOWBALLTEST_H

#include "layer/control/treenodetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeResultFollowBallTest :
		public TreeNodeTest
	{
		CPPUNIT_TEST_SUITE(TreeNodeResultFollowBallTest);
		CPPUNIT_TEST(execute_true_bothRobotsGetGoToCalls);
		CPPUNIT_TEST(execute_noLastRobot_correctRobotIsChoosen);
		CPPUNIT_TEST_SUITE_END();

	private:
		virtual TreeNode *createTestNode();

	private:
		void execute_true_bothRobotsGetGoToCalls();
		void execute_noLastRobot_correctRobotIsChoosen();

	};
}
}
}

#endif


