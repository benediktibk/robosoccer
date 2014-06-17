#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODERESULTLEAVEGOALZONETEST_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODERESULTLEAVEGOALZONETEST_H

#include "layer/control/treenodetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeResultLeaveGoalZoneTest :
		public TreeNodeTest
	{
		CPPUNIT_TEST_SUITE(TreeNodeResultLeaveGoalZoneTest);
		CPPUNIT_TEST(execute_true_robotsGetGoToCalls);
		CPPUNIT_TEST_SUITE_END();

	private:
		virtual TreeNode *createTestNode();

	private:
		void execute_true_robotsGetGoToCalls();

	};
}
}
}

#endif


