#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODERESULTSHOOTTEST_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODERESULTSHOOTTEST_H

#include "layer/control/treenodetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeResultShootTest :
		public TreeNodeTest
	{
		CPPUNIT_TEST_SUITE(TreeNodeResultShootTest);
		CPPUNIT_TEST_SUITE_END();

	private:
		virtual TreeNode *createTestNode();

	private:

	};
}
}
}

#endif


