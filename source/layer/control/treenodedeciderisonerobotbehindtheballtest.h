#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISONEROBOTBEHINDTHEBALLTEST_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISONEROBOTBEHINDTHEBALLTEST_H

#include "layer/control/treenodetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeDeciderIsOneRobotBehindTheBallTest :
		public TreeNodeTest
	{
		CPPUNIT_TEST_SUITE(TreeNodeDeciderIsOneRobotBehindTheBallTest);
		CPPUNIT_TEST(getChild_ballInOwnZone_defend);
		CPPUNIT_TEST(getChild_ballInEnemyZone_attack);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual TreeNode* createTestNode();

	private:
		void getChild_ballInOwnZone_defend();
		void getChild_ballInEnemyZone_attack();


	};
}
}
}

#endif


