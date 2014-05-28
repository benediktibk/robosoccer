#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODERESULTATTACKBALLTEST_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODERESULTATTACKBALLTEST_H

#include "layer/control/treenodetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeResultAttackBallTest :
		public TreeNodeTest
	{
		CPPUNIT_TEST_SUITE(TreeNodeResultAttackBallTest);
		CPPUNIT_TEST(execute_bothRobotsShouldMove_moveMethodsGetCalled);
		CPPUNIT_TEST_SUITE_END();

	private:
		virtual TreeNode *createTestNode();

	private:
		void execute_bothRobotsShouldMove_moveMethodsGetCalled();

	};
}
}
}

#endif


