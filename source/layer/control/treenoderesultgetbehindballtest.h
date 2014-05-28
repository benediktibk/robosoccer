#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODERESULTGETBEHINDBALLTEST_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODERESULTGETBEHINDBALLTEST_H

#include "layer/control/treenodetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeResultGetBehindBallTest :
		public TreeNodeTest
	{
		CPPUNIT_TEST_SUITE(TreeNodeResultGetBehindBallTest);
		CPPUNIT_TEST_SUITE_END();

	private:
		virtual TreeNode *createTestNode();

	private:

	};
}
}
}

#endif


